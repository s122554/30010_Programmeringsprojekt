     void printStartScreen(){
          int i,j;
          int asciilen = 100, asciiheigth = 45;
          
          char array[100][45] = {
              "                                                                 +@                                 ",
              "                                                              `#@@@                                 ",
              "                                                           .@@@@@#@`                                ",
              "                                                        :@@@@#;''@@                                 ",
              "                                                     '@@@@#;;;;;#@@@                                ",
              "                                                 .+@@@@+;;;;;;';;@'                                 ",
              "                              `+@+              @@@@';;';;;';;:,#@.                                 ",
              "                           .#@@@@              ,@;;;;;;;;;;;'@@@@;                                  ",
              "                        ,@@@@@'@@             .@@;';;;':.;:;@#.                                     ",
              "                     :@@@@#;';;@+    '@;     ,@@.;';,'@@,;;@@                                       ",
              "                  ,@@@@#;';''';@;`+@@@@      .@@:,#@#';@,;:@#                                       ",
              "                `@@@+;;'';';;;+@@@@@'@@    ;@@.+@+;;:;;@;;;@.                   .`                  ",
              "               '@@;'';';;;'::#@@#;;';@:`#@@@@#;+::;;;,;':;+@                ,@@@@@@,                ",
              "              '@#;'';'';,+@@@#;;;;;;#@@@@@':;:;@';;@@@@,;;@@            `+@@@@@';'@@.               ",
              "             .@+;'';::@@@@#;:';;:':,@@#@.:;;:,'#;:;;;@@::;@+         ;@@@@@+;;';;;;@@               ",
              "             @@;';;+@@@@#@::;;;;;@#':;;:,;;@@#@;::::,@@;;:@`     .#@#@@#;:';;;;;;;;'@`              ",
              "            .@,;';;@@@@@@@,;,::;:;;:;:;:,;;;:#@.:;:,#@':,#@   '@@@@@@';;;';;;;;;;;';@'              ",
              "            #@';;:+';;:;:@@@@;;;;;:;@+::,:;::@@,:##;:#,::@@@@@@@+;;#@.';';;;;;;':;;:@#              ",
              "            @#;;;;:;;:;;;;@@+;:.,::@#:;@;;,.'@@;;:;,:@.#@@@@@;;;;;:@@;:;;;;;;;;;';;;@@              ",
              "            @#;:;;;;:;:;:;@@.:;@':;;:;##:'@#::@::::.:@@@@+;;;;;;;,,@:;';;;;:,#,;;;;;@#              ",
              "            '@;;:;:::;;:;;@@,:;::;::;,@::,::,+:,,#@@@#';;';;;;;';:@@.;;;;;#@@@@;;:;:@'              ",
              "             @+,;;;:;::;:#@@::+.;;,,,:+.,;;:.@@@@@';:';:;;;;;:;;:;'@,,+;;:@@ @+;;;;'@`              ",
              "             `@@@@@@:;;::@@';;+.,:@`,::.,,#@@@+;;:@;';;;;;;;;';;:.#@@@#;:;@:,@.;;::@@               ",
              "               ;@@@,:;::+@@.:,@;::@#,.+@@@#;;;;:+@@';:;;;;'::,+@@@+;:#,:;'@#@#:;:;:@#               ",
              "            :@@@@;:;;,:,@@@::;':,;@@@@@':;;;;;:;;;';;;;;,,:;@@+;;:;;#@,;;@@@';;:;;#@                ",
              "        #@@@@@#:;,:::,:@@#@:,#@#@@@#:;;;;;;;;:';;@@;,,#@@:;;:;;:;;:;@@;;:@'::::::;@;                ",
              "       @@@@':::;,:::,,@@ @+@@@@@'';:;;;;;:;;:;;:,@@@@@+:@;::.;::;:;;@+:::;:;;:::;@@                 ",
              "      .@',:;::;,:,:,;@@@@@@@+;;:;;:;;::;:;;:,:#@@@+@@;;::::@;:;;::.#.;:;;:::::,@@#                  ",
              "      @@@`;,::,,::.@@@@@#;:::;:;::;:;:;:,:#@@@+@:;;@@,:;,::::::+@@@@;:::::::::@@,                  ;",
              "      #@@;,::,,,,+@@@':;:;:';:;:::;:,:@@@@+:::#@.:'@@::#:::+::@@':#@:;::::::::'@#                #@ ",
              "     @@;:,,,,,,#@#:::::;;:;::;::.;@@@@#@;::::;@@;:@@'::+;;+@::::::@@::::;@,::::#@@            `@@@  ",
              "   ,@@@:,,,,,@@@@;:::::::;;:;::@@@@#:;@::::;;:@'::@@.;:.::@@:::::#@,.:::@@.:::::#@@,       .;@@@@   ",
              "    @@,,,.#@@@.@@::::;;,,;;:::'@@+:.::#:::.,'@@.::::::;:::@;:::::@@@,:::@@@::::::;@@@@@@@@@@@@@@    ",
              "   #@`;@@@@; '@@':;,.'@@@@.:::::;:@::;.::@@@':@::::;::@::'@.::,.,#@@:::;@.@.::::::::+##++';:,#@`    ",
              "  '@@@@@:   .@#,.'@@@@@@@'::;;:;::@::@;:#:::::#::::::::::@@::@@@@+@':::+@ @+::::::,::,::,,:,@@,     ",
              " ,@@:       @@@@@@#, @@,::::::::::;::;::::::::.:::::::.:,@#::,,::,@.,,:@@ ,@`,::,,,:::,:,,,'@@      ",
              "           @@@#,     @@`::;:::::,..::.:'.:::,@,:;@@::+:::@,,:::::;@,:::@@  @@,:,:,,,,,,,:,,@@@@     ",
              "          ,.        `@@:,;:::;@@@@::#::@@@:,@#::#@',:+,:#@,,:::,:@@:,:,@'   @@.,,,,,,,,,,,.@@       ",
              "                    ,@..+::,,@@;@#::@::,:,::@,:,@@.::.:,@@:,..,;#@',:::@.    @@`,,,,,,,,,,@@        ",
              "                    +@@@@:,:;@  @,,,@,::,:,,@,:,@@:,,,,,@@@@@@@@@@`+@#'@      #@#.,,,,,.`'@         ",
              "                    @; @,:::@@ .@,:'@:,:::,+@.:#@@@@@..#@+;.    :@@@@@@@       .@@#`,,,.@@@;        ",
              "                      `@.:,:@@ #@:.@@';#@@@@@@@@@+:@:@@@@           @            ,@@@@@@@.          ",
              "                      +@,.@`@, @@@@@#@@@@',`       @@@@                             ;;.             ",
              "                      @@@@@@@  @#;#               '@:                                               ",
              "                      +':#@;@                                                                       ",
              "                          `                                                                         ",
              }

          startPos=((frameBounds[2]-frameBounds[0])/2)-asciilen/2;

                    for(i=0;i<=asciilen;i++){
                        for(j=0;j<=asciiheight;j++){
                          gotoxy(i+startPos,j);
                          printf(array[i][j]);
                        }
                    }
     }

          





