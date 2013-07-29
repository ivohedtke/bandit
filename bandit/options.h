#ifndef BANDIT_OPTIONS_H
#define BANDIT_OPTIONS_H

namespace bandit { namespace detail {

    // TODO: print any unknown options
    // TODO: check for parser errors
    struct options
    {

      options(int argc, char* argv[])
      {
        argc -= (argc>0); argv += (argc>0); // Skip program name (argv[0]) if present
        option::Stats stats(usage(), argc, argv);
        options_.resize(stats.options_max);
        std::vector<option::Option> buffer(stats.buffer_max);
        option::Parser parse(usage(), argc, argv, options_.data(), buffer.data());
        parsed_ok_ = !parse.error();
      }

      bool help() const
      {
        return options_[HELP];
      }

      void print_usage() const
      {
        option::printUsage(std::cout, usage());
      }

      bool version() const
      {
        return options_[VERSION];
      }

      const char* reporter() const
      {
        return options_[REPORTER].arg;
      }

      bool color() const
      {
        return options_[COLOR];
      }

      private:
        enum option_index { UNKNOWN, VERSION, HELP, REPORTER, COLOR };
        static const option::Descriptor* usage()
        {
          static const option::Descriptor usage[] =
          {
            {UNKNOWN, 0, "", "", option::Arg::None,         "USAGE: <executable> [options]\n\n"
                                                            "Options:" },
            {VERSION, 0, "", "version", option::Arg::None, "  --version, \tPrint version of bandit"},
            {HELP, 0, "", "help", option::Arg::None,        "  --help, \tPrint usage and exit."},
            {REPORTER, 0, "", "reporter", option::Arg::Optional, "  --reporter, \tSelect reporter (dots, singleline, xunit)"},
            {COLOR, 0, "", "color", option::Arg::None,     "  --color, \tUse ANSI colors in output"},
            {0, 0, 0, 0, 0, 0}
          };

          return usage;
        }

      private:
        std::vector<option::Option> options_;
        bool parsed_ok_;

    };

}}

#endif
