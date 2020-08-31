#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>

/*
 Экран 1.
 Выбор: пойти налево или направо.
 
 Экран 2.
 Выбор:
    * Пошёл налево:
        - Внезапная смерть
    * Пошёл направо:
        - Подняться вверх или спуститься вниз
 Экран 3.
    * Поднялись вверх:
        - Встречаем дракона, сражаемся
    * Спустились вниз:
        - Сражаемся с полчищем крыс
 
 Геймплей:
 * Дракон умеет:
    - Дышать огнём 1 раз в 5 своих ходов, снимает 20hp, вероятность 60%
    - Случайно равновероятно:
        → Взмах крыльями, чтобы сбросить игрока с высоты,
          на которую он поднялся.
              § Игрок умрёт от падения,
                если его здоровье меньше 30%, так как
                у него не хватит сил удержаться.
              § Иначе ничего не произойдёт.
        → Физическая атака когтями.
              § У игрока снимается 10hp
 
 * Крысы умеют:
     - Каждый ход крысы атакуют игрока.
       Одна крыса снимает 3hp с вероятностью 60%.
       Количестко крыс в одной атаке: 3-7
 
 * Игрок умеет:
     - Стрелять из лука
         → Стреляет в дракона: шанс попадания 75%, урон 15hp.
     - Атаковать мечом
         → Рубить дракона, если дракон
           в предыдущем ходе атаковал когтями,
           урон 25hp.
         → Рубить крыс: с вероятностью 60%
           убить от 3-х до 7-и крыс
     - Раздавить одну крысу ногой
     
 = Эпилог =
 * Игрок умирает из-за потери здоровья
 * Игрок побеждает
 */

bool battleWithDragon() {
    int dragon = 200;
    int last_fire_attack = 0, fire_damage = 20, chance_fire = 60;
    int wings_death_hp_limit = 30;
    int claws_damage = 10; bool is_claws = false;
    
    int player = 100;
    int arrow_damage = 15, arrow_chance = 75;
    int sword_damage = 25;
    
    bool is_player_turn = true;
    
    while(dragon > 0 && player > 0) {
        system("cls");
        printf("=== БИТВА С ДРАКОНОМ ===\n");
        printf("Ты: %d |>   <| %d :Дракон\n\n", player, dragon);
        
        if(is_player_turn) {
            printf("\nТвой ход, игрок\n\n");
            printf("1. Выстрелить из лука (%d%%, damage: %dhp)\n", arrow_chance, arrow_damage);
            if(is_claws) {
                printf("2. Рубить дракона мечом (100%%, damage: %d)\n", sword_damage);
            }
            printf("Выбирай, игрок: ");
            int x;
            scanf("%d", &x);
            
            switch(x) {
                case 1:
                    if(rand() % 101 <= arrow_chance) {
                        printf("Стрела попала в дракона!\n");
                        dragon -= arrow_damage;
                    } else {
                        printf("Дракон уклонился!\n");
                    }
                    break;
                case 2:
                    if(is_claws) {
                        dragon -= sword_damage;
                        printf("Ты рубанул по дракону мечом!\n");
                        break;
                    }
                    [[fallthrough]];
                default:
                    printf("Не мухлюй, такого варианта нет.\nТы пропускаешь ход\n");
            }
            is_claws = false;
        }
        
        else { // Dragon turn
            if(last_fire_attack % 5 == 0) {
                printf("Дракон окатил тебя потоком огня! ");
                if(rand() % 101 <= chance_fire) {
                    printf("Ты пострадал!\n");
                    player -= fire_damage;
                } else {
                    printf("Тебе чудом удалось уклониться!\n");
                }
            } else {
                if(rand() % 2 == 0) {
                    printf("Дракон взмахнул крыльями и создал воздушный удар!\n");
                    if(player <= wings_death_hp_limit) {
                        printf("Ты умерл от падения, не устояв перед порывом воздуха!\n");
                        player = 0;
                    } else {
                        printf("Тебе хватило сил остаться на ногах после мощного порыва!\n");
                    }
                } else {
                    printf("Дракон прошёлся по тебе когтями!\n");
                    is_claws = true;
                    player -= claws_damage;
                }
            }
            ++last_fire_attack;
        }
        system("pause");
        
        is_player_turn = !is_player_turn;
    }
    
    return player > 0;
}

bool battleWithRat() {
    int player = 100;
    int sword_deaths_min = 3;
    int sword_deaths_max = 7;
    int sword_chance = 60;
    
    int rat_damage = 3;
    int count_rats = 42;
    int min_rats_in_attack = 3;
    int max_rats_in_attack = 7;
    int rat_damage_chance = 60;
    
    bool is_player_turn = false;
    
    while(count_rats > 0 && player > 0) {
        system("cls");
        printf("=== БИТВА С КРЫСАМИ ===\n");
        printf("Ты: %d |>   <| %d :Крысы\n\n", player, count_rats);
        
        if(is_player_turn) {
            printf("\nТвой ход, игрок!\n\n");
            printf("1. Раздавить одну крысу (100%%)\n");
            printf(
                "2. Рубануть по стае крыс мечом (%d%%, affected: %d-%d)\n",
                sword_chance, sword_deaths_min, sword_deaths_max
            );
            printf("Выбирай, игрок: ");
            int x;
            scanf("%d", &x);
            
            if(x == 1) {
                printf("Крыса жалобно пищит умирает под твоим каблуком...\n");
                --count_rats;
            
            } else if(x == 2) {
                int cur_sword_deaths =
                    sword_deaths_min +
                    rand() % (sword_deaths_max - sword_deaths_min + 1);
                if(rand() % 101 <= sword_chance && cur_sword_deaths != 0) {
                    printf(
                        "Ты размахнулся мечом и "
                        "благословил нескольких крыс на полёт в небеса\n"
                    );
                    count_rats -= cur_sword_deaths;
                } else {
                    printf("Ни одна из крыс не пострадала\n");
                }
            } else {
                printf("Не мухлюй! Такого варианта нет.\nТы пропускаешь ход\n");
            }
            
        } else { // Rat turn
            int rats_in_attack =
                min_rats_in_attack +
                rand() % (max_rats_in_attack - min_rats_in_attack + 1);
            if(rand() % 101 <= rat_damage_chance && rats_in_attack != 0) {
                printf("Ты не смог уклониться от укусов крыс\n");
                player -= rats_in_attack * rat_damage;
            } else {
                printf("Ни одна из крыс тебя не задела\n");
            }
        }
        
        is_player_turn = !is_player_turn;
        system("pause");
    }
    
    return player > 0;
}

int main() {
    srand(unsigned(time(0)));
    printf("Куда хочешь пойти?\n1. Налево\n2. Направо\nВыбирай: ");
    int x;
    scanf("%d", &x);
    
    if(x == 1) {
        printf("\n=== Ходить налево плохо, ты умер! ===\n");
        system("pause");
        return 0;
    }
    
    system("cls");
    printf("Ты пошёл направо. Что теперь?\n1. Подняться\n2. Спуститься\nВыбирай: ");
    scanf("%d", &x);
    
    bool is_win_dragon = false, is_win_rats = false;
    if(x == 1) {
        is_win_dragon = battleWithDragon();
    } else {
        is_win_rats = battleWithRat();
    }
    
    system("cls");
    if(is_win_dragon) {
        printf("Ты жёстко расфигачил дракона в пух и прах .-.\n");
    } else if(is_win_rats) {
        printf("Ты порубил крыс на самый мясистый шашлык\n");
    } else {
        printf("Ты покинул этот мир с миром :(\n");
    }
    
    system("pause");
}
