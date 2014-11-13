#include <iostream>
#include <array>

static const int startVal = 500;
static const int goalVal  = 500;
static const int voidVal  = 50;

enum class Material {
    Wall,
    Start,
    Goal,
    Void
};

static const Material w = Material::Wall;
static const Material s = Material::Start;
static const Material g = Material::Goal;
static const Material v = Material::Void;

class Cell {
public:
    bool isVoid;
    int life;
    Material ty;
    Cell(Material m) : ty(m) {
        if(m == w) { isVoid = false; life = -1000000; }
        if(m == s) { isVoid = true; life = startVal; }
        if(m == g) { isVoid = true; life = goalVal; }
        if(m == v) { isVoid = true; life = voidVal; }
    }
    void show() {
        if(ty == w) std::cout << 'x';
        if(ty == s) std::cout << 'S';
        if(ty == g) std::cout << 'G';
        if(ty == v) {
            if(life == 0) std::cout << ' ';
            if(0 < life && life <=10) std::cout << '0';
            if(10 < life && life <=20) std::cout << '1';
            if(20 < life && life <=30) std::cout << '2';
            if(30 < life && life <=40) std::cout << '3';
            if(40 < life && life <=50) std::cout << '4';
            if(50 < life && life <=60) std::cout << '5';
            if(60 < life && life <=70) std::cout << '6';
            if(70 < life && life <=80) std::cout << '7';
            if(80 < life && life <=90) std::cout << '8';
            if(90 < life && life <=100) std::cout << '9';
            if(100 < life) std::cout << '!';
        }
    }
    // void next() {
    //     if(ty == v) life -= 5;
    //     if(life >= 50 || ty == s || ty == g){
    //         // 横にあげる
    //     }
    //     if(life < 0) life = 0; // 死
    // }
};

class World {
    using Map = std::array<std::array<Cell, 26>, 13>; // 決め打ち
    Map map;
public:
    World() : map({{
                { w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w },
                { w, v, w, v, w, v, v, v, v, v, v, v, v, v, v, v, v, v, v, v, v, v, v, v, v, w },
                { w, s, w, v, w, v, v, w, v, v, w, w, w, w, w, w, w, w, w, w, w, w, w, v, v, w },
                { w, v, w, v, v, v, w, v, v, v, v, w, w, w, w, w, w, w, w, w, w, w, w, v, v, w },
                { w, v, v, v, v, w, v, v, v, v, v, v, v, v, v, v, v, v, v, v, v, v, v, v, v, w },
                { w, w, w, w, w, w, w, w, w, w, w, w, w, w, v, w, w, w, w, w, w, w, w, w, w, w },
                { w, v, v, v, v, v, v, v, v, v, v, v, v, v, v, v, v, v, v, v, v, v, v, v, v, w },
                { w, w, v, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w },
                { w, v, v, v, v, v, v, w, v, v, v, v, v, v, v, v, v, v, v, v, v, v, g, v, v, w },
                { w, v, v, w, v, v, v, v, v, v, w, w, w, w, w, w, w, w, w, w, w, v, w, v, v, w },
                { w, v, v, v, v, w, v, v, v, v, v, v, v, v, v, w, w, w, w, w, w, v, w, v, v, w },
                { w, v, v, v, v, v, v, v, w, v, v, v, v, v, v, v, v, v, v, v, v, v, v, v, v, w },
                { w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w }
            }}) {} // ひどい
    void show() const {
        for(auto es: map) {
            for(auto e: es) e.show();
            std::cout << std::endl;
        }
    }
    void next() {
        Map old(map);
        for(int i(1); i < 12; ++i) { // サイズ
            for(int j(1); j < 25; ++j) {
                Cell cell = old[i][j];
                Cell& next = map[i][j];
                if(cell.ty == v) next.life -=2;
                if(cell.life >= 20 || cell.ty == s || cell.ty == g) {
                    // give
                    int cnt = 0;
                    // if(old[i-1][j].isVoid && old[i-1][j].life > 0) ++cnt;
                    // if(old[i+1][j].isVoid && old[i+1][j].life > 0) ++cnt;
                    // if(old[i][j-1].isVoid && old[i][j-1].life > 0) ++cnt;
                    // if(old[i][j+1].isVoid && old[i][j+1].life > 0) ++cnt;
                       if(old[i-1][j].isVoid) ++cnt;
                       if(old[i+1][j].isVoid) ++cnt;
                       if(old[i][j-1].isVoid) ++cnt;
                       if(old[i][j+1].isVoid) ++cnt;

                   if(cnt<=2){
                       int val = cell.life / (cnt+1);
                       next.life -= (cell.life - val);
                       if(old[i-1][j].isVoid) map[i-1][j].life += val;
                       if(old[i+1][j].isVoid) map[i+1][j].life += val;
                       if(old[i][j-1].isVoid) map[i][j-1].life += val;
                       if(old[i][j+1].isVoid) map[i][j+1].life += val;
                   } else {
                       int val = cell.life / (cnt+1);
                       next.life -= (cell.life - val);
                       if(old[i-1][j].isVoid && old[i-1][j].life > 0) map[i-1][j].life += val;
                       if(old[i+1][j].isVoid && old[i+1][j].life > 0) map[i+1][j].life += val;
                       if(old[i][j-1].isVoid && old[i][j-1].life > 0) map[i][j-1].life += val;
                       if(old[i][j+1].isVoid && old[i][j+1].life > 0) map[i][j+1].life += val;
                   }
                   if(cell.ty == s || cell.ty == g){
                       next.life = startVal;
                   }
                }
                if(next.life < 0) next.life = 0;
            }
        }
    }
};

int main(int, char**) {
    World map;

    for(int i(0); i < 1000; ++i) {
       if(i%10 == 0)
        map.show();
        map.next();
    }
    return 0;
}
