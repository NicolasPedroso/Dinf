#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>

#include "Jogador.h"
#include "Inimigos.h"

#define X_TELA 800
#define Y_TELA 400
#define NUM_INIMIGOS 50

unsigned char colisao2D(jogador *elemento_primeiro, jogador *elemento_segudo){

	if ((((elemento_segudo->y-elemento_segudo->lado/2 >= elemento_primeiro->y-elemento_primeiro->lado/2) && (elemento_primeiro->y+elemento_primeiro->lado/2 >= elemento_segudo->y-elemento_segudo->lado/2)) ||
		((elemento_primeiro->y-elemento_primeiro->lado/2 >= elemento_segudo->y-elemento_segudo->lado/2) && (elemento_segudo->y+elemento_segudo->lado/2 >= elemento_primeiro->y-elemento_primeiro->lado/2))) &&
		(((elemento_segudo->x-elemento_segudo->lado/2 >= elemento_primeiro->x-elemento_primeiro->lado/2) && (elemento_primeiro->x+elemento_primeiro->lado/2 >= elemento_segudo->x-elemento_segudo->lado/2)) ||
		((elemento_primeiro->x-elemento_primeiro->lado/2 >= elemento_segudo->x-elemento_segudo->lado/2) && (elemento_segudo->x+elemento_segudo->lado/2 >= elemento_primeiro->x-elemento_primeiro->lado/2)))) return 1;
	else return 0;
}

unsigned char veMorte(jogador *assassino, jogador *vitima){

	bala *anterior = NULL;
	for (bala *id = assassino->arma->tiros; id != NULL; id = (bala*) id->prox){
		if ((id->x >= vitima->x - vitima->lado/2) && (id->x <= vitima->x + vitima->lado/2) &&
		   (id->y >= vitima->y - vitima->lado/2) && (id->y <= vitima->y + vitima->lado/2)){
			vitima->vida--;
			if (vitima->vida){
				if (anterior){
					anterior->prox = id->prox;
					destroiBala(id);
					id = (bala*) anterior->prox;
				}
				else {
					assassino->arma->tiros = (bala*) id->prox;
					destroiBala(id);
					id = assassino->arma->tiros;
				}
				return 0;
			}
			else return 1;
		}
		anterior = id;
	}
	return 0;
}

void atualizaBalas(jogador *jogador){
	
	bala *anterior = NULL;
	for (bala *id = jogador->arma->tiros; id != NULL;){
		if (!id->trajetoria) id->x -= MOVI_BALA;
		else if (id->trajetoria == 1) id->x += MOVI_BALA;
	
		
		if ((id->x < 0) || (id->x > X_TELA)){
			if (anterior){
				anterior->prox = id->prox;
				destroiBala(id);
				id = (bala*) anterior->prox;
			}
			else {
				jogador->arma->tiros = (bala*) id->prox;
				destroiBala(id);
				id = jogador->arma->tiros;
			}
		}
		else{
			anterior = id;
			id = (bala*) id->prox;
		}
	}
}

void atualizaPosicao(jogador *jogador1, jogador *jogador2){

	if (jogador1->controle->esquerda){
		moveJogador(jogador1, 1, 0, X_TELA, Y_TELA);
		if (colisao2D(jogador1, jogador2)) moveJogador(jogador1, -1, 0, X_TELA, Y_TELA);
	}
	if (jogador1->controle->direita){
		moveJogador(jogador1, 1, 1, X_TELA, Y_TELA);
		if (colisao2D(jogador1, jogador2)) moveJogador(jogador1, -1, 1, X_TELA, Y_TELA);
	}
	if (jogador1->controle->cima) {
		moveJogador(jogador1, 1, 2, X_TELA, Y_TELA);
		if (colisao2D(jogador1, jogador2)) moveJogador(jogador1, -1, 2, X_TELA, Y_TELA);
	}
	if (jogador1->controle->baixo){
		moveJogador(jogador1, 1, 3, X_TELA, Y_TELA);
		if (colisao2D(jogador1, jogador2)) moveJogador(jogador1, -1, 3, X_TELA, Y_TELA);
	}
	
	if (jogador2->controle->esquerda){
		moveJogador(jogador2, 1, 0, X_TELA, Y_TELA);
		if (colisao2D(jogador2, jogador1)) moveJogador(jogador2, -1, 0, X_TELA, Y_TELA);
	}
	
	if (jogador2->controle->direita){
		moveJogador(jogador2, 1, 1, X_TELA, Y_TELA);
		if (colisao2D(jogador2, jogador1)) moveJogador(jogador2, -1, 1, X_TELA, Y_TELA);
	}
	
	if (jogador2->controle->cima){
		moveJogador(jogador2, 1, 2, X_TELA, Y_TELA);
		if (colisao2D(jogador2, jogador1)) moveJogador(jogador2, -1, 2, X_TELA, Y_TELA);
	}
	if (jogador2->controle->baixo){
		moveJogador(jogador2, 1, 3, X_TELA, Y_TELA);
		if (colisao2D(jogador2, jogador1)) moveJogador(jogador2, -1, 3, X_TELA, Y_TELA);
	}
	if (jogador1->controle->atira){
		if (!jogador1->arma->tempo){
			jogadorAtira(jogador1);
			jogador1->arma->tempo = REGARGA_PISTOLA;
		} 
	}
	if (jogador2->controle->atira){
		if (!jogador2->arma->tempo){
			jogadorAtira(jogador2);
			jogador2->arma->tempo = REGARGA_PISTOLA;
		}
	}
	atualizaBalas(jogador1);
	atualizaBalas(jogador2);
}

void desenhaInimigos(inimigo *lista) {
    for (inimigo *id = lista; id != NULL; id = id->prox) {
        al_draw_filled_circle(id->x, id->y, 20, id->cor); // Desenha um círculo preenchido com a cor do inimigo
    }
}


int main(){
	
	inimigo *inimigos = NULL;
	int inimigos_ativos = 0;

	al_init();
	al_init_primitives_addon();
    al_init_font_addon();
    al_init_ttf_addon();
	
	al_install_keyboard();

	ALLEGRO_TIMER* timer = al_create_timer(1.0 / 30.0);
	ALLEGRO_TIMER* timer_inimigos = al_create_timer(1.0 / 2.0); // Timer para gerar inimigos a cada 0.5s
	ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
    ALLEGRO_FONT *fontTTF = al_load_ttf_font("acessorios/minecraft_font.ttf", 15, 0);
	ALLEGRO_DISPLAY* disp = al_create_display(X_TELA, Y_TELA);
    al_set_window_position(disp, 300 ,300);
    al_set_window_title(disp, "Space Impact");
    //al_set_display_icon(disp, path);


	al_register_event_source(queue, al_get_keyboard_event_source());
	al_register_event_source(queue, al_get_display_event_source(disp));
	al_register_event_source(queue, al_get_timer_event_source(timer));
	al_register_event_source(queue, al_get_timer_event_source(timer_inimigos));

	jogador* jogador1 = criaJogador(20, 1, 10, Y_TELA/2, X_TELA, Y_TELA);
	if (!jogador1) return 1;
	jogador* jogador2 = criaJogador(20, 0, X_TELA-10, Y_TELA/2, X_TELA, Y_TELA);
	if (!jogador2) return 2;

	ALLEGRO_EVENT event;
	al_start_timer(timer);
	al_start_timer(timer_inimigos);
	unsigned char p1k = 0, p2k = 0;
	while(1){
		al_wait_for_event(queue, &event);
		
		if (p1k || p2k){
			al_clear_to_color(al_map_rgb(0, 0, 0));
			if (p2k && p1k) al_draw_text(fontTTF, al_map_rgb(255, 255, 255), X_TELA/2 - 40, Y_TELA/2-15, 0, "EMPATE!");
			else if (p2k) al_draw_text(fontTTF, al_map_rgb(255, 0, 0), X_TELA/2 - 75, Y_TELA/2-15, 0, "JOGADOR 1 GANHOU!");
			else if (p1k) al_draw_text(fontTTF, al_map_rgb(0, 0, 255), X_TELA/2 - 75, Y_TELA/2-15, 0, "JOGADOR 2 GANHOU!");
			al_draw_text(fontTTF, al_map_rgb(255, 255, 255), X_TELA/2 - 110, Y_TELA/2+5, 0, "PRESSIONE ESPACO PARA SAIR");
			al_flip_display();

			if ((event.type == 10) && (event.keyboard.keycode == 75)) break;
			else if (event.type == 42) break;
		}
		else{
			if (event.type == 30){
				atualizaPosicao(jogador1, jogador2);
				if (inimigos_ativos < NUM_INIMIGOS) {
                    int tipo = rand() % 4; // Escolha aleatória de tipo de inimigo
                	float x = X_TELA;
                	float y = rand() % Y_TELA; // Posição aleatória na tela
                	adicionaInimigo(&inimigos, tipo, x, y);
                	inimigos_ativos++;
                }
				atualizaInimigos(inimigos, jogador1, jogador2);
				p1k = veMorte(jogador2, jogador1);
				p2k = veMorte(jogador1, jogador2);
				al_clear_to_color(al_map_rgb(0, 0, 0));
				al_draw_filled_rectangle(jogador1->x-jogador1->lado/2, jogador1->y-jogador1->lado/2, jogador1->x+jogador1->lado/2, jogador1->y+jogador1->lado/2, al_map_rgb(255, 0, 0));
				al_draw_filled_rectangle(jogador2->x-jogador2->lado/2, jogador2->y-jogador2->lado/2, jogador2->x+jogador2->lado/2, jogador2->y+jogador2->lado/2, al_map_rgb(0, 0, 255));
	    		/*for (inimigo *id = inimigos; id != NULL; id = id->prox) {
                	al_draw_filled_rectangle(id->x - id->lado / 2, id->y - id->lado / 2, id->x + id->lado / 2, id->y + id->lado / 2, al_map_rgb((rand()%255), (rand()%255), (rand()%255))); // Cor do inimigo
           		}*/
				desenhaInimigos(inimigos);
				for (bala *id = jogador1->arma->tiros; id != NULL; id = (bala*) id->prox) al_draw_filled_circle(id->x, id->y, 2, al_map_rgb(255, 0, 0));
	    		if (jogador1->arma->tempo) jogador1->arma->tempo--;
	    		for (bala *id = jogador2->arma->tiros; id != NULL; id = (bala*) id->prox) al_draw_filled_circle(id->x, id->y, 2, al_map_rgb(0, 0, 255));
	    		if (jogador2->arma->tempo) jogador2->arma->tempo--;
	    		al_flip_display();
			}
			else if ((event.type == 10) || (event.type == 12)){
				if (event.keyboard.keycode == 1) controleEsquerda(jogador1->controle);
				else if (event.keyboard.keycode == 4) controleDireita(jogador1->controle);
				else if (event.keyboard.keycode == 23) controleCima(jogador1->controle);
				else if (event.keyboard.keycode == 19) controleBaixo(jogador1->controle);
				else if (event.keyboard.keycode == 82) controleEsquerda(jogador2->controle);
				else if (event.keyboard.keycode == 83) controleDireita(jogador2->controle);
				else if (event.keyboard.keycode == 84) controleCima(jogador2->controle);
				else if (event.keyboard.keycode == 85) controleBaixo(jogador2->controle);
				else if (event.keyboard.keycode == 3) controleAtira(jogador1->controle);
				else if (event.keyboard.keycode == 216) controleAtira(jogador2->controle);
			}																																			
			else if (event.type == 42) break;
		}
	}

	al_destroy_font(fontTTF);
	al_destroy_display(disp);
	al_destroy_timer(timer);
	al_destroy_event_queue(queue);
	destroiJogador(jogador1);
	destroiJogador(jogador2);

	return 0;
}