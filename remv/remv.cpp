// Copyright (c) 2009 Dmitry Goncharov
//
// Distributed under the BSD License.
// (See accompanying file COPYING).

// "$Id:"

#include <cstdio>
#include <string>
#include <iostream>
#include <stdexcept>
#include <boost/filesystem.hpp>
#include <boost/regex.hpp>
#include <boost/program_options.hpp>

using std::cout;
using std::endl;
using std::cerr;
using std::string;
namespace fs = boost::filesystem;

void move(fs::path const& p, boost::regex const& r, string const& fmt, bool pretend, bool force)
{
    string const f = p.filename();
    string const newf = boost::regex_replace(f, r, fmt, boost::match_default);
    if (f != newf)
    {
        fs::path const newp(p.parent_path() / fs::path(newf));
        cout << p << " -> " << newp << endl;
        if (!pretend)
        {
            if (force)
            {
                int const s = std::rename(p.string().c_str(), newp.string().c_str());
                if (s < 0)
                {
                    cerr << "Cannot rename " << p << endl;
                    throw std::runtime_error(std::strerror(errno));
                }
            }
            else
                fs::rename(p, newp);
        }
    }
}

void moveall(fs::path const& root, boost::regex const& r, string const& fmt, bool recursive, bool pretend, bool force)
{
    if (fs::is_directory(root))
    {
        typedef fs::directory_iterator it_t;
        for (it_t it(root), last = it_t(); it != last; ++it)
        {
            fs::path const& p = it->path();
            if (recursive && fs::is_directory(it->status()))
                moveall(p, r, fmt, recursive, pretend, force);
            move(p, r, fmt, pretend, force);
        }
    }
    else
        move(root, r, fmt, pretend, force);
}

struct options
{
    options()
        : recursive(false)
    {}

    string regex;
    string format;
    fs::path path;
    bool recursive;
    bool pretend;
    bool force;
};


std::ostream& operator<<(std::ostream& out, options const& opts)
{
    out << "regex: " << opts.regex
        << ", format: " << opts.format
        << ", path: " << opts.path.string()
        << ", recursive: " << opts.recursive
        << ", pretend: " << opts.pretend
        << ", force: " << opts.force
        << "\n";
    return out;
}

int main(int argc, char* argv[])
{
    namespace po = boost::program_options;
    string const exe = fs::path(argv[0]).leaf();
    options opts;
    {
        po::options_description desc(
            "Usage: " + exe + " regex format [path] [options]"
            "\n"
            "\nStarting from #path recursively finds files and directories"
	    "\nwhich match the regular expression, specified by #regex,"
            "\nand moves them according to the format, specified by #format."
    
            "\n\nThe Boost.Regex library is used for regex processing."
            "\n(See boost.org for details on supported regex syntaxes)."
            "\n\nIf path is not specified . is used."

            "\n\nExamples: Moving all uppercase chars to lowercase chars: " + exe  + " \"(\\w+)\" \"\\L\\\\1\""
            "\n\nOptions");
    
        desc.add_options()
            ("help,h",
                "this help message")
            ("version,v",
                "print the version")
            ("recursive,r",
                "move directories recursively")
            ("pretend,p",
                "don't actually move")
            ("force,f",
                "overwrite existing files");

        po::positional_options_description pos;
        pos.add("regex", 1);
        pos.add("format", 1);
        pos.add("path", 1);

        po::options_description hidden("Hidden options");
        hidden.add_options()
            ("regex", po::value<string>(&opts.regex))
            ("format", po::value<string>(&opts.format))
            ("path", po::value<fs::path>(&opts.path)->default_value(fs::path(".")));

        po::options_description all_opts("All options");
        all_opts.add(desc);
        all_opts.add(hidden);

        po::variables_map vm;
        po::store(po::command_line_parser(argc, argv).options(all_opts).positional(pos).run(), vm);
        notify(vm);
        opts.recursive = vm.count("recursive"); //TODO: have the lib to init it.
        opts.pretend = vm.count("pretend"); //TODO: have the lib to init it.
        opts.force = vm.count("force"); //TODO: have the lib to init it.

        if (vm.count("help"))
        {
            cout << desc << endl;
            return 0;
        }
        if (vm.count("version"))
        {
            cout << "0.12" << endl;
            return 0;
        }
        if (!vm.count("regex")) //TODO: have the lib to report this
        {
            std::cerr << fs::path(argv[0]).leaf() << ": missing regex operand" << endl;
            return 1;
        }
        if (!vm.count("format"))
        {
            std::cerr << fs::path(argv[0]).leaf() << ": missing format operand" << endl;
            return 2;
        }
        cout << opts << endl;
    }

    boost::regex const r(opts.regex);
    moveall(opts.path, r, opts.format, opts.recursive, opts.pretend, opts.force);

    return 0;
}

