#include "network.hpp"

namespace server {
    void network_Test() {
//        try {
//            ServicesManager servicesManager;
//            servicesManager.registerService(std::make_unique<VersionService>());
//
//            Game game;
//            Game.getPlayer(make_unique<User>("Paul",23));
//            servicesManager.registerService(make_unique<UserService>(std::ref(Game)));

//            struct MHD_Daemon *d;
//            if (argc != 2) {
//                printf("%s PORT\n", argv[0]);
//                return 1;
//            }
//            d = MHD_start_daemon(// MHD_USE_SELECT_INTERNALLY | MHD_USE_DEBUG | MHD_USE_POLL,
//                    MHD_USE_SELECT_INTERNALLY | MHD_USE_DEBUG,
//                    // MHD_USE_THREAD_PER_CONNECTION | MHD_USE_DEBUG | MHD_USE_POLL,
//                    // MHD_USE_THREAD_PER_CONNECTION | MHD_USE_DEBUG,
//                    atoi(argv[1]),
//                    NULL, NULL, 
//                    &main_handler, (void*) &servicesManager,
//                    MHD_OPTION_NOTIFY_COMPLETED, request_completed, NULL,
//                    MHD_OPTION_END);
//            if (d == NULL)
//                return 1;
//            cout << "Pressez <entrée> pour arrêter le serveur" << endl;
//            (void) getc(stdin);
//            MHD_stop_daemon(d);
//        }
//        catch(exception& e) {
//            cerr << "Exception: " << e.what() << endl;
//        }
    }
}
