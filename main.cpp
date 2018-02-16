// Stardard I/O
# include <stdio.h>

// Stardard Library
# include <stdlib.h>

// Just for chdir()
# include <unistd.h>

// String
# include <string.h>

// Assert
# include <assert.h>

// STL
# include <bits/stdc++.h>

# define version "0.1.0"
# define name "ZOJ-updater"

bool Compare_File(const char* file1,const char* file2) {
    std::ifstream f1(file1), f2(file2);

    while (f1.good() && f2.good()) {
        char a, b;
        f1 >> a; f2 >> b;
        if (a != b) return 1;
    }
    if (f1.good() ^ f2.good()) return 1;

    return 0;
}

int main(int argc, char ** argv) {
    if (argc > 1) {
        for (int i = 1; i < argc; i++) {
            if (0 == strcmp(argv[i], "-v") || 
                0 == strcmp(argv[i], "--version")) {
                    printf("%s %s\n", name, version);
                    return 0;
            } else if (0 == strcmp(argv[i], "--help")) {
                puts("Usage: zoj-update-detector [options]");
                puts("Options: ");
                puts("  -v         Display version information");
                puts("  --version  Equals to -v");
                puts("  --help     Display this imformation");
                return 0;
            } else {
                printf("Unknown option : %s\n", argv[i]);
                return 0;
            }
        }
    }
    system("wget https://raw.githubusercontent.com/sky-develop-team/zoj/master/package.json");
    
    puts("Download Finish...");

    chdir("..");

    if (Compare_File("zoj/package.json", "zoj-update-detector/package.json")) {
        system("rm zoj-updater/package.json");
        puts("Do you want to update[y/n]?");
        char buf[1024];
        scanf("%s", buf);
        if (0 == strcmp(buf, "y") ||
            0 == strcmp(buf, "Y") ||
            0 == strcmp(buf, "")) {
            puts("start updating...");
        } else {
            puts("stop.");
            return 0;
        }
    } else {
        system("rm zoj-updater/package.json");
        puts("Your ZOJ is the latest version.");
        return 0;
    }

    system("cp zoj/uploads/ /tmp -r");
    system("cp zoj/config.json /tmp");  
    system("rm -rf zoj");
    system("git clone https://github.com/sky-develop-team/zoj.git");
    system("cp /tmp/uploads/ zoj -r");
    system("cp /tmp/config.json zoj");
    system("rm -rf /tmp/uploads");
    chdir("zoj");
    system("npm install");

    puts("Finish.");
    return 0;
}
