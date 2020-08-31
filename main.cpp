#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>

/*
 ��࠭ 1.
 �롮�: ���� ������ ��� ���ࠢ�.
 
 ��࠭ 2.
 �롮�:
    * ���� ������:
        - ��������� ᬥ���
    * ���� ���ࠢ�:
        - ��������� ����� ��� �������� ����
 ��࠭ 3.
    * ����﫨�� �����:
        - ����砥� �ࠪ���, �ࠦ�����
    * ����⨫��� ����:
        - �ࠦ����� � ����饬 ����
 
 ��������:
 * �ࠪ�� 㬥��:
    - ����� ���� 1 ࠧ � 5 ᢮�� 室��, ᭨���� 20hp, ����⭮��� 60%
    - ���砩�� ࠢ������⭮:
        ? ����� ����ﬨ, �⮡� ����� ��ப� � �����,
          �� ������ �� �������.
              ? ��ப ���� �� �������,
                �᫨ ��� ���஢� ����� 30%, ⠪ ���
                � ���� �� 墠�� ᨫ 㤥ঠ����.
              ? ���� ��祣� �� �ந������.
        ? �����᪠� �⠪� ����ﬨ.
              ? � ��ப� ᭨������ 10hp
 
 * ����� 㬥��:
     - ����� 室 ����� �⠪��� ��ப�.
       ���� ���� ᭨���� 3hp � ����⭮���� 60%.
       ������⪮ ���� � ����� �⠪�: 3-7
 
 * ��ப 㬥��:
     - ��५��� �� �㪠
         ? ��५�� � �ࠪ���: 蠭� ��������� 75%, �஭ 15hp.
     - �⠪����� ��箬
         ? �㡨�� �ࠪ���, �᫨ �ࠪ��
           � �।��饬 室� �⠪���� ����ﬨ,
           �஭ 25hp.
         ? �㡨�� ����: � ����⭮���� 60%
           㡨�� �� 3-� �� 7-� ����
     - ��������� ���� ����� �����
     
 = ������ =
 * ��ப 㬨ࠥ� ��-�� ���� ���஢��
 * ��ப ���������
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
        printf("=== ����� � �������� ===\n");
        printf("��: %d |>   <| %d :�ࠪ��\n\n", player, dragon);
        
        if(is_player_turn) {
            printf("\n���� 室, ��ப\n\n");
            printf("1. ����५��� �� �㪠 (%d%%, damage: %dhp)\n", arrow_chance, arrow_damage);
            if(is_claws) {
                printf("2. �㡨�� �ࠪ��� ��箬 (100%%, damage: %d)\n", sword_damage);
            }
            printf("�롨ࠩ, ��ப: ");
            int x;
            scanf("%d", &x);
            
            switch(x) {
                case 1:
                    if(rand() % 101 <= arrow_chance) {
                        printf("��५� ������ � �ࠪ���!\n");
                        dragon -= arrow_damage;
                    } else {
                        printf("�ࠪ�� 㪫������!\n");
                    }
                    break;
                case 2:
                    if(is_claws) {
                        dragon -= sword_damage;
                        printf("�� �㡠�� �� �ࠪ��� ��箬!\n");
                        break;
                    }
                    [[fallthrough]];
                default:
                    printf("�� ����, ⠪��� ��ਠ�� ���.\n�� �ய�᪠��� 室\n");
            }
            is_claws = false;
        }
        
        else { // Dragon turn
            if(last_fire_attack % 5 == 0) {
                printf("�ࠪ�� ���⨫ ⥡� ��⮪�� ����! ");
                if(rand() % 101 <= chance_fire) {
                    printf("�� ����ࠤ��!\n");
                    player -= fire_damage;
                } else {
                    printf("���� �㤮� 㤠���� 㪫�������!\n");
                }
            } else {
                if(rand() % 2 == 0) {
                    printf("�ࠪ�� ������ ����ﬨ � ᮧ��� ������� 㤠�!\n");
                    if(player <= wings_death_hp_limit) {
                        printf("�� 㬥� �� �������, �� ���� ��। ���뢮� ������!\n");
                        player = 0;
                    } else {
                        printf("���� 墠⨫� ᨫ ������� �� ����� ��᫥ ��魮�� ���뢠!\n");
                    }
                } else {
                    printf("�ࠪ�� ������ �� ⥡� ����ﬨ!\n");
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
        printf("=== ����� � ������� ===\n");
        printf("��: %d |>   <| %d :�����\n\n", player, count_rats);
        
        if(is_player_turn) {
            printf("\n���� 室, ��ப!\n\n");
            printf("1. ��������� ���� ����� (100%%)\n");
            printf(
                "2. �㡠���� �� �⠥ ���� ��箬 (%d%%, affected: %d-%d)\n",
                sword_chance, sword_deaths_min, sword_deaths_max
            );
            printf("�롨ࠩ, ��ப: ");
            int x;
            scanf("%d", &x);
            
            if(x == 1) {
                printf("���� ������� ���� 㬨ࠥ� ��� ⢮�� ����㪮�...\n");
                --count_rats;
            
            } else if(x == 2) {
                int cur_sword_deaths =
                    sword_deaths_min +
                    rand() % (sword_deaths_max - sword_deaths_min + 1);
                if(rand() % 101 <= sword_chance && cur_sword_deaths != 0) {
                    printf(
                        "�� ࠧ������ ��箬 � "
                        "�����᫮��� ��᪮�쪨� ���� �� ����� � �����\n"
                    );
                    count_rats -= cur_sword_deaths;
                } else {
                    printf("�� ���� �� ���� �� ����ࠤ���\n");
                }
            } else {
                printf("�� ����! ������ ��ਠ�� ���.\n�� �ய�᪠��� 室\n");
            }
            
        } else { // Rat turn
            int rats_in_attack =
                min_rats_in_attack +
                rand() % (max_rats_in_attack - min_rats_in_attack + 1);
            if(rand() % 101 <= rat_damage_chance && rats_in_attack != 0) {
                printf("�� �� ᬮ� 㪫������� �� ��ᮢ ����\n");
                player -= rats_in_attack * rat_damage;
            } else {
                printf("�� ���� �� ���� ⥡� �� ������\n");
            }
        }
        
        is_player_turn = !is_player_turn;
        system("pause");
    }
    
    return player > 0;
}

int main() {
    srand(unsigned(time(0)));
    printf("�㤠 ���� ����?\n1. ������\n2. ���ࠢ�\n�롨ࠩ: ");
    int x;
    scanf("%d", &x);
    
    if(x == 1) {
        printf("\n=== ������ ������ ����, �� 㬥�! ===\n");
        system("pause");
        return 0;
    }
    
    system("cls");
    printf("�� ���� ���ࠢ�. �� ⥯���?\n1. ���������\n2. ���������\n�롨ࠩ: ");
    scanf("%d", &x);
    
    bool is_win_dragon = false, is_win_rats = false;
    if(x == 1) {
        is_win_dragon = battleWithDragon();
    } else {
        is_win_rats = battleWithRat();
    }
    
    system("cls");
    if(is_win_dragon) {
        printf("�� ���⪮ ��䨣�稫 �ࠪ��� � ��� � ��� .-.\n");
    } else if(is_win_rats) {
        printf("�� ���㡨� ���� �� ᠬ� ������ ���\n");
    } else {
        printf("�� ������ ��� ��� � ��஬ :(\n");
    }
    
    system("pause");
}