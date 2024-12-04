#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>

#include <stdio.h>

#include "Jogador.h"
#include "Inimigos.h"

int main(){
	
	inimigo *inimigos = NULL;
	int inimigos_ativos = 0;

	al_init();
	al_init_primitives_addon();
    al_init_font_addon();
    al_init_ttf_addon();
	al_init_image_addon();
	
	al_install_keyboard();

	ALLEGRO_TIMER* timer = al_create_timer(1.0 / 30.0);
	ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
    ALLEGRO_FONT *fontTTF = al_load_ttf_font("acessorios/minecraft_font.ttf", 15, 0);
	
	/*Struct info*/
	ALLEGRO_MONITOR_INFO info;

	/*Resolucao do monitor do usuario*/
	int resolucaoXComp, resolucaoYComp;

	al_get_monitor_info(0, &info);

	resolucaoXComp = info.x2 - info.x1;
	resolucaoYComp = info.y2 - info.y1;

	/*Seta o display disp*/
	al_set_new_display_flags(ALLEGRO_FULLSCREEN_WINDOW);
	ALLEGRO_DISPLAY* disp = al_create_display(resolucaoXComp, resolucaoYComp);
    
	/*redimensionamento*/
	float redimensaoX, redimensaoY;

	redimensaoX = resolucaoXComp / (float) X_TELA;
	redimensaoY = resolucaoYComp / (float) Y_TELA;

	/*Funcoes de redimensao*/
	ALLEGRO_TRANSFORM transformar;

	al_identity_transform(&transformar);
	al_scale_transform(&transformar, redimensaoX, redimensaoY);
	al_use_transform(&transformar);
	al_hide_mouse_cursor(disp);

	
	al_set_window_position(disp, 300 ,300);
    al_set_window_title(disp, "Space Impact");
    //al_set_display_icon(disp, path);

	/*Imagens e derivados*/
	ALLEGRO_BITMAP *jogadorEsquerda = al_load_bitmap("acessorios/jogador_esquerda.png");
	ALLEGRO_BITMAP *jogadorDireita = al_load_bitmap("acessorios/jogador_direita.png");
	ALLEGRO_BITMAP *jogadorCima = al_load_bitmap("acessorios/jogador_cima.png");
	ALLEGRO_BITMAP *jogadorBaixo = al_load_bitmap("acessorios/jogador_baixo.png");

	al_register_event_source(queue, al_get_keyboard_event_source());
	al_register_event_source(queue, al_get_display_event_source(disp));
	al_register_event_source(queue, al_get_timer_event_source(timer));

	jogador* jogador1 = criaJogador(20, 1, 10, Y_TELA/2, X_TELA, Y_TELA);
	if (!jogador1) return 1;
	jogador* jogador2 = criaJogador(20, 0, X_TELA-10, Y_TELA/2, X_TELA, Y_TELA);
	if (!jogador2) return 2;

	ALLEGRO_EVENT event;
	al_start_timer(timer);
	unsigned char p1k = 0, p2k = 0;
	unsigned char vivo = 0;
	
	while (1) {
    	al_wait_for_event(queue, &event);
    
    	if (vivo) {
        	al_clear_to_color(al_map_rgb(0, 0, 0));
        	al_draw_text(fontTTF, al_map_rgb(12, 238, 26), X_TELA / 2 - 75, Y_TELA / 2 - 15, 0, "MORREU PROS MOBS RUIM!");
       	 	al_draw_text(fontTTF, al_map_rgb(12, 238, 26), X_TELA / 2 - 110, Y_TELA / 2 + 5, 0, "PRESSIONE ESPACO PARA SAIR");
        	al_flip_display();
        
			if (event.type == 10 && event.keyboard.keycode == ALLEGRO_KEY_R) vivo = 0;
        	if ((event.type == 10 && event.keyboard.keycode == 75) || (event.type == 42)) break;
		}
    	else if (p1k || p2k) {
        	al_clear_to_color(al_map_rgb(0, 0, 0));
        	if (p2k && p1k) {
            	al_draw_text(fontTTF, al_map_rgb(255, 255, 255), X_TELA / 2 - 40, Y_TELA / 2 - 15, 0, "EMPATE!");
        	} else if (p2k) {
            	al_draw_text(fontTTF, al_map_rgb(255, 0, 0), X_TELA / 2 - 75, Y_TELA / 2 - 15, 0, "JOGADOR 1 GANHOU!");
        	} else if (p1k) {
            	al_draw_text(fontTTF, al_map_rgb(0, 0, 255), X_TELA / 2 - 75, Y_TELA / 2 - 15, 0, "JOGADOR 2 GANHOU!");
        	}
        	al_draw_text(fontTTF, al_map_rgb(255, 255, 255), X_TELA / 2 - 110, Y_TELA / 2 + 5, 0, "PRESSIONE ESPACO PARA SAIR");
        	al_flip_display();
        
        	if ((event.type == 10 && event.keyboard.keycode == 75) || (event.type == 42)) break;
    	}
    	else {
			if (event.type == 30) {
            	al_clear_to_color(al_map_rgb(0, 0, 0)); // Limpando a tela apenas uma vez por iteração
	            atualizaPosicao(jogador1, jogador2);
    	        if (inimigos_ativos < 500 /* MAX_INIMIGOS */) {
        	        int tipo = rand() % 4; // Escolha aleatória de tipo de inimigo
            	    float x = X_TELA;
                	float y = rand() % Y_TELA; // Posição aleatória na tela
	                adicionaInimigo(&inimigos, tipo, x, y);
    	            inimigos_ativos++;
        	    }
            	atualizaInimigos(&inimigos, jogador1);
	            p1k = veMortePVP(jogador2, jogador1);
    	        p2k = veMortePVP(jogador1, jogador2);
        	    vivo = veMortePVE(jogador1);
            
            	// Desenho de elementos
	            al_draw_filled_rectangle(jogador1->x - jogador1->lado / 2, jogador1->y - jogador1->lado / 2, jogador1->x + jogador1->lado / 2, jogador1->y + jogador1->lado / 2, al_map_rgb(255, 0, 0));
    	        al_draw_filled_rectangle(jogador2->x - jogador2->lado / 2, jogador2->y - jogador2->lado / 2, jogador2->x + jogador2->lado / 2, jogador2->y + jogador2->lado / 2, al_map_rgb(0, 0, 255));
        	    desenhaInimigos(inimigos);
            	balasInimigos(inimigos);


				/*Desenha jogador1*/
				if(jogador1->face == DIRECAO_ESQUERDA) al_draw_bitmap(jogadorEsquerda, jogador1->x - 24, jogador1->y - 24, 0);
				if(jogador1->face == DIRECAO_DIREITA) al_draw_bitmap(jogadorDireita, jogador1->x - 24, jogador1->y - 24, 0);
				if(jogador1->face == DIRECAO_CIMA) al_draw_bitmap(jogadorCima, jogador1->x - 24, jogador1->y - 24, 0);
				if(jogador1->face == DIRECAO_BAIXO) al_draw_bitmap(jogadorBaixo, jogador1->x - 24, jogador1->y - 24, 0);

				/*Desenha jogador2*/
				if(jogador2->face == DIRECAO_ESQUERDA) al_draw_bitmap(jogadorEsquerda, jogador2->x - 24, jogador2->y - 24, 0);
				if(jogador2->face == DIRECAO_DIREITA) al_draw_bitmap(jogadorDireita, jogador2->x - 24, jogador2->y - 24, 0);
				if(jogador2->face == DIRECAO_CIMA) al_draw_bitmap(jogadorCima, jogador2->x - 24, jogador2->y - 24, 0);
				if(jogador2->face == DIRECAO_BAIXO) al_draw_bitmap(jogadorBaixo, jogador2->x - 24, jogador2->y - 24, 0);
 
				/*Desenha inimigos*/
				


				
            
            	for (bala *id = jogador1->arma->tiros; id != NULL; id = (bala*) id->prox) {
                	al_draw_filled_circle(id->x, id->y, 2, al_map_rgb(255, 0, 0));
            	}
	            if (jogador1->arma->tempo) jogador1->arma->tempo--;
    	        for (bala *id = jogador2->arma->tiros; id != NULL; id = (bala*) id->prox) {
        	        al_draw_filled_circle(id->x, id->y, 2, al_map_rgb(0, 0, 255));
            	}
	            if (jogador2->arma->tempo) jogador2->arma->tempo--;
	
    	        al_flip_display();
        	}
        		else if ((event.type == 10) || (event.type == 12)) {
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

	al_destroy_bitmap(jogadorBaixo);
	al_destroy_bitmap(jogadorCima);
	al_destroy_bitmap(jogadorDireita);
	al_destroy_bitmap(jogadorEsquerda);
	
	
	al_destroy_font(fontTTF);
	al_destroy_display(disp);
	al_destroy_timer(timer);
	al_destroy_event_queue(queue);
	destroiJogador(jogador1);
	destroiJogador(jogador2);
	return 0;
}