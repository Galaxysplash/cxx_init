#pragma once

constexpr const char *conanfile_txt = "# uncomment for external dependencies\n# [requires]\n# dependency 1\n# dependency 2\n# ...\n\n[generators]\nCMakeDeps\nCMakeToolchain";