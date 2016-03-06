#include "app.h"


App::App():BaseApp(){
    panelPower.setup(&race.players);
    panelRanking.setup(&race.players);
    panelTime.setup(&race.players);
}

