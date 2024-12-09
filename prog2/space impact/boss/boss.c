#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <math.h>
#include <stdio.h>

#define LARGURA_TELA 800
#define ALTURA_TELA 600

int main() {
    al_init();
    al_init_primitives_addon();
    al_init_image_addon();
    al_install_keyboard();

    ALLEGRO_DISPLAY* display = al_create_display(LARGURA_TELA, ALTURA_TELA);
    ALLEGRO_BITMAP* sprite = al_create_bitmap(50, 50); // Cria um bitmap de exemplo (quadrado)
    ALLEGRO_TIMER* timer = al_create_timer(1.0 / 30.0);
    ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();

    // Registra os eventos
    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_timer_event_source(timer));

    // Cria um ponto inicial para o movimento
    float ponto_x = LARGURA_TELA / 2.0;
    float ponto_y = ALTURA_TELA / 2.0;
    float raio = 250.0; // Raio do círculo
    float angulo = 0.0; // Ângulo inicial
    float velocidade_rotacao = 0.07; // Velocidade de rotação

    // Desenha um quadrado branco como a sprite
    al_set_target_bitmap(sprite);
    al_clear_to_color(al_map_rgb(255, 255, 255));
    al_set_target_bitmap(al_get_backbuffer(display));

    // Carrega o bitmap do chefe
    ALLEGRO_BITMAP* chefao2 = al_load_bitmap("../teste/acessorios/chefe_2.png");
    if (!chefao2) {
        fprintf(stderr, "Erro ao carregar o bitmap do chefe.\n");
        return -1;
    }

    al_start_timer(timer);

    ALLEGRO_EVENT event;
    while (1) {
        al_wait_for_event(queue, &event);

        if (event.type == ALLEGRO_EVENT_KEY_DOWN && event.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
            break; // Encerra o loop se a tecla ESC for pressionada
        }

        if (event.type == ALLEGRO_EVENT_TIMER) {
            // Calcula a posição (x, y) da sprite em torno do ponto (ponto_x, ponto_y)
            float x = ponto_x + raio * cos(angulo);
            float y = ponto_y + raio * sin(angulo);

            // Limpa a tela
            al_clear_to_color(al_map_rgb(0, 0, 0));

            // Desenha a sprite rotacionada em torno do ponto (ponto_x, ponto_y)
            al_draw_rotated_bitmap(chefao2, al_get_bitmap_width(chefao2) / 2.0, al_get_bitmap_height(chefao2) / 2.0, x, y, angulo, 0);

            // Desenha o chefe no centro da tela
            float chefao_x = LARGURA_TELA / 2.0 - al_get_bitmap_width(chefao2) / 2.0;
            float chefao_y = ALTURA_TELA / 2.0 - al_get_bitmap_height(chefao2) / 2.0;
            al_draw_bitmap(chefao2, chefao_x, chefao_y, 0);

            // Atualiza a tela
            al_flip_display();

            // Atualiza o ângulo para o próximo quadro
            angulo += velocidade_rotacao;
            if (angulo >= 2 * M_PI) {
                angulo -= 2 * M_PI; // Mantém o ângulo no intervalo de [0, 2*PI]
            }
        }
    }

    al_destroy_bitmap(sprite);
    al_destroy_bitmap(chefao2);
    al_destroy_display(display);
    al_destroy_event_queue(queue);
    al_destroy_timer(timer);

    return 0;
}
