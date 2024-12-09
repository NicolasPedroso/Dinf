#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>

#include <stdio.h>

#include "Jogador.h"
#include "Inimigos.h"
#include "Chefao.h"

#define VELOCIDADE_DESLIZAMENTO 2
#define MAX_VIDA 100

int main(){
	
	inimigo *inimigos = NULL;
	int regargaOnda = 150;
	char pontos[100];
	int modoJogo = 0;
	int jogo = 0;
	unsigned char p1k = 0, p2k = 0;
	unsigned char vivo = 0;
	srand(time(NULL)); 
	

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
	/*Jogador 75% de vida*/
	ALLEGRO_BITMAP *jogador75Esquerda = al_load_bitmap("acessorios/jogador_75_esquerda.png");
	ALLEGRO_BITMAP *jogador75Direita = al_load_bitmap("acessorios/jogador_75_direita.png");
	ALLEGRO_BITMAP *jogador75Cima = al_load_bitmap("acessorios/jogador_75_cima.png");
	ALLEGRO_BITMAP *jogador75Baixo = al_load_bitmap("acessorios/jogador_75_baixo.png");
	/*Jogador 50% de vida*/
	ALLEGRO_BITMAP *jogador50Esquerda = al_load_bitmap("acessorios/jogador_50_esquerda.png");
	ALLEGRO_BITMAP *jogador50Direita = al_load_bitmap("acessorios/jogador_50_direita.png");
	ALLEGRO_BITMAP *jogador50Cima = al_load_bitmap("acessorios/jogador_50_cima.png");
	ALLEGRO_BITMAP *jogador50Baixo = al_load_bitmap("acessorios/jogador_50_baixo.png");
	/*Jogador 25% de vida*/
	ALLEGRO_BITMAP *jogador25Esquerda = al_load_bitmap("acessorios/jogador_25_esquerda.png");
	ALLEGRO_BITMAP *jogador25Direita = al_load_bitmap("acessorios/jogador_25_direita.png");
	ALLEGRO_BITMAP *jogador25Cima = al_load_bitmap("acessorios/jogador_25_cima.png");
	ALLEGRO_BITMAP *jogador25Baixo = al_load_bitmap("acessorios/jogador_25_baixo.png");
	
	ALLEGRO_BITMAP *fundo1 = al_load_bitmap("acessorios/fase_1.png");
	ALLEGRO_BITMAP *fundo2 = al_load_bitmap("acessorios/fase_2.png");

	/*Cores*/
	ALLEGRO_COLOR verde = al_map_rgb(12, 238, 26);
	ALLEGRO_COLOR vemelho = al_map_rgb(255, 0, 0);
	ALLEGRO_COLOR azul = al_map_rgb(0, 0, 255);
	ALLEGRO_COLOR branco = al_map_rgb(255, 255, 255);
	ALLEGRO_COLOR preto = al_map_rgb(0, 0, 0);
	



	int larguraFundo = al_get_bitmap_width(fundo1);/*iamgens de tamanho igual pode ser usado no dois fundos*/
	float posicaoFundo = 0;



	al_register_event_source(queue, al_get_keyboard_event_source());
	al_register_event_source(queue, al_get_display_event_source(disp));
	al_register_event_source(queue, al_get_timer_event_source(timer));

	jogador* jogador1 = criaJogador(MAX_VIDA, 20, 1, 10, Y_TELA/2, X_TELA, Y_TELA);
	if (!jogador1) return 1;
	jogador* jogador2 = criaJogador(MAX_VIDA, 20, 0, X_TELA-10, Y_TELA/2, X_TELA, Y_TELA);
	if (!jogador2) return 2;

	chefao* chefao1 = criaChefao(0 , X_TELA - 45, Y_TELA/2);
	chefao* chefao2 = criaChefao(1 , X_TELA, Y_TELA/2);

	ALLEGRO_EVENT event;
	al_start_timer(timer);

	while (1) {
		al_wait_for_event(queue, &event);

		if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
			if (event.keyboard.keycode == ALLEGRO_KEY_W) {
				modoJogo--;
				if (modoJogo < 0) modoJogo = 0;
			} else if (event.keyboard.keycode == ALLEGRO_KEY_S) {
				modoJogo++;
				if (modoJogo > 3) modoJogo = 3;
			} else if (event.keyboard.keycode == ALLEGRO_KEY_ENTER) {
				if(modoJogo == 3) {
					jogo = 1;
				}
				break;
			}
		}

		al_clear_to_color(preto);

		if (modoJogo == 0) {
			al_draw_text(fontTTF, verde, X_TELA / 2, Y_TELA / 2 - 10, ALLEGRO_ALIGN_CENTER, "FASE1");
		} else {
			al_draw_text(fontTTF, branco, X_TELA / 2, Y_TELA / 2 - 10, ALLEGRO_ALIGN_CENTER, "FASE1");
		}

		if (modoJogo == 1) {
			al_draw_text(fontTTF, verde, X_TELA / 2, Y_TELA / 2 + 5, ALLEGRO_ALIGN_CENTER, "FASE2");
		} else {
			al_draw_text(fontTTF, branco, X_TELA / 2, Y_TELA / 2 + 5, ALLEGRO_ALIGN_CENTER, "FASE2");
		}

		if (modoJogo == 2) {
			al_draw_text(fontTTF, verde, X_TELA / 2, Y_TELA / 2 + 20, ALLEGRO_ALIGN_CENTER, "FASE3");
		} else {
			al_draw_text(fontTTF, branco, X_TELA / 2, Y_TELA / 2 + 20, ALLEGRO_ALIGN_CENTER, "FASE3");
		}

		if (modoJogo == 3) {
			al_draw_text(fontTTF, verde, X_TELA / 2, Y_TELA / 2 + 35, ALLEGRO_ALIGN_CENTER, "SAIR");
		} else {
			al_draw_text(fontTTF, branco, X_TELA / 2, Y_TELA / 2 + 35, ALLEGRO_ALIGN_CENTER, "SAIR");
		}

		al_flip_display();
	}

	while(jogo != 1 ) {

		al_wait_for_event(queue, &event);

		posicaoFundo -= VELOCIDADE_DESLIZAMENTO;

		if (posicaoFundo <= -larguraFundo) { posicaoFundo = 0;}

		if(modoJogo == 0){/*Fase1*/
			if (vivo) {
				al_clear_to_color(al_map_rgb(0, 0, 0));
				al_draw_text(fontTTF, al_map_rgb(12, 238, 26), X_TELA / 2 - 75, Y_TELA / 2 - 15, 0, "MORREU!");
				al_draw_text(fontTTF, al_map_rgb(12, 238, 26), X_TELA / 2 - 110, Y_TELA / 2 + 5, 0, "PRESSIONE ESPACO PARA SAIR");
				al_flip_display();
			
				if ((event.type == 10 && event.keyboard.keycode == 75) || (event.type == 42)) break;
			} else {
				if (event.type == 30) {
            		al_clear_to_color(al_map_rgb(0, 0, 0)); 
	            
					/*Desliza a tela*/
					al_draw_bitmap(fundo1, posicaoFundo, 0, 0);
					al_draw_bitmap(fundo1, posicaoFundo + larguraFundo, 0, 0);
				
					atualizaPosicao(jogador1, jogador2);
					
					if(jogador1->pontos < 500){
						if(regargaOnda <= 0) {
							for (int i = 0; i < MAX_INIMIGOS; i++) {
								adicionaInimigo(&inimigos, rand() % 4, X_TELA + 50, rand() % Y_TELA);
							}
							regargaOnda += 450;
						} else { 
							regargaOnda -= 1;
							atualizaInimigos(&inimigos, jogador1);
						}
					} else {
						atualizaInimigos(&inimigos, jogador1);
						atualizaChefao(chefao2, jogador1);
						if(chefao2->vida <= 0){
							while(jogo != 1){
								al_wait_for_event(queue, &event);
								al_clear_to_color(al_map_rgb(0, 0, 0));
								al_draw_text(fontTTF, al_map_rgb(12, 238, 26), X_TELA / 2 - 75, Y_TELA / 2 - 15, 0, "CHEFE DERROTADO!");
								al_draw_text(fontTTF, al_map_rgb(12, 238, 26), X_TELA / 2 - 150, Y_TELA / 2, 0, "PRESSIONE ESPACO PARA SAIR");
								al_flip_display();
								if ((event.type == 10 && event.keyboard.keycode == 75) || (event.type == 42)) jogo = 1;
							}
						}
					}
			
					/*Pontos jogador*/
					sprintf(pontos, "SCORE: %d", jogador1->pontos);
					al_draw_text(fontTTF, al_map_rgb(12, 238, 26), 10, 10, 0, pontos);
				
					/*Vida jogador*/
					sprintf(pontos, "VIDA: %d", jogador1->vida);
					al_draw_text(fontTTF, al_map_rgb(12, 238, 26), 10, 30, 0, pontos);

	        		vivo = veMortePVE(jogador1);
            
					/*Desenha inimigos e seus tiros*/
					desenhaInimigos(inimigos);
					balasInimigos(inimigos);


					/*Desenha jogador1*/
					if(jogador1->vida > MAX_VIDA*0.75) {
						if(jogador1->face == DIRECAO_ESQUERDA) al_draw_bitmap(jogadorEsquerda, jogador1->x - 24, jogador1->y - 24, 0);
						if(jogador1->face == DIRECAO_DIREITA) al_draw_bitmap(jogadorDireita, jogador1->x - 24, jogador1->y - 24, 0);
						if(jogador1->face == DIRECAO_CIMA) al_draw_bitmap(jogadorCima, jogador1->x - 24, jogador1->y - 24, 0);
						if(jogador1->face == DIRECAO_BAIXO) al_draw_bitmap(jogadorBaixo, jogador1->x - 24, jogador1->y - 24, 0);
					} else if(jogador1->vida <= MAX_VIDA*0.75 && jogador1->vida > MAX_VIDA*0.50) {
						if(jogador1->face == DIRECAO_ESQUERDA) al_draw_bitmap(jogador75Esquerda, jogador1->x - 24, jogador1->y - 24, 0);
						if(jogador1->face == DIRECAO_DIREITA) al_draw_bitmap(jogador75Direita, jogador1->x - 24, jogador1->y - 24, 0);
						if(jogador1->face == DIRECAO_CIMA) al_draw_bitmap(jogador75Cima, jogador1->x - 24, jogador1->y - 24, 0);
						if(jogador1->face == DIRECAO_BAIXO) al_draw_bitmap(jogador75Baixo, jogador1->x - 24, jogador1->y - 24, 0);
					} else if(jogador1->vida <= MAX_VIDA*0.50 && jogador1->vida > MAX_VIDA*0.25) {
						if(jogador1->face == DIRECAO_ESQUERDA) al_draw_bitmap(jogador50Esquerda, jogador1->x - 24, jogador1->y - 24, 0);
						if(jogador1->face == DIRECAO_DIREITA) al_draw_bitmap(jogador50Direita, jogador1->x - 24, jogador1->y - 24, 0);
						if(jogador1->face == DIRECAO_CIMA) al_draw_bitmap(jogador50Cima, jogador1->x - 24, jogador1->y - 24, 0);
						if(jogador1->face == DIRECAO_BAIXO) al_draw_bitmap(jogador50Baixo, jogador1->x - 24, jogador1->y - 24, 0);
					} else if(jogador1->vida <= MAX_VIDA*0.25) {
						if(jogador1->face == DIRECAO_ESQUERDA) al_draw_bitmap(jogador25Esquerda, jogador1->x - 24, jogador1->y - 24, 0);
						if(jogador1->face == DIRECAO_DIREITA) al_draw_bitmap(jogador25Direita, jogador1->x - 24, jogador1->y - 24, 0);
						if(jogador1->face == DIRECAO_CIMA) al_draw_bitmap(jogador25Cima, jogador1->x - 24, jogador1->y - 24, 0);
						if(jogador1->face == DIRECAO_BAIXO) al_draw_bitmap(jogador25Baixo, jogador1->x - 24, jogador1->y - 24, 0);
					}



					/*Desenha balas do jogador1*/
					for (bala *id = jogador1->arma->tiros; id != NULL; id = (bala*) id->prox) {
						al_draw_filled_circle(id->x, id->y, 2, al_map_rgb(255, 0, 0));
					}
					if (jogador1->arma->tempo) jogador1->arma->tempo--;
					
					al_flip_display();
				}
					else if ((event.type == 10) || (event.type == 12)) {
						if (event.keyboard.keycode == 1) controleEsquerda(jogador1->controle);
						else if (event.keyboard.keycode == 4) controleDireita(jogador1->controle);
						else if (event.keyboard.keycode == 23) controleCima(jogador1->controle);
						else if (event.keyboard.keycode == 19) controleBaixo(jogador1->controle);
						else if (event.keyboard.keycode == 3) controleAtira(jogador1->controle);
					}
					else if (event.type == 42) break;
				}
		} else if(modoJogo == 1){ /*fase2*/
			if (vivo) {
				al_clear_to_color(al_map_rgb(0, 0, 0));
				al_draw_text(fontTTF, al_map_rgb(12, 238, 26), X_TELA / 2 - 75, Y_TELA / 2 - 15, 0, "MORREU!");
				al_draw_text(fontTTF, al_map_rgb(12, 238, 26), X_TELA / 2 - 110, Y_TELA / 2 + 5, 0, "PRESSIONE ESPACO PARA SAIR");
				al_flip_display();
			
				if ((event.type == 10 && event.keyboard.keycode == 75) || (event.type == 42)) break;
			} else {
				if (event.type == 30) {
            		al_clear_to_color(al_map_rgb(0, 0, 0)); 
	            
					/*Desliza a tela*/
					al_draw_bitmap(fundo2, posicaoFundo, 0, 0);
					al_draw_bitmap(fundo2, posicaoFundo + larguraFundo, 0, 0);
				
					atualizaPosicao(jogador1, jogador2);

					if(jogador1->pontos < 500){
						if(regargaOnda <= 0) {
							for (int i = 0; i < MAX_INIMIGOS; i++) {
								adicionaInimigo(&inimigos, rand() % 4, X_TELA + 50, rand() % Y_TELA);
							}
							regargaOnda += 450;
						} else { 
							regargaOnda -= 1;
							atualizaInimigos(&inimigos, jogador1);
						}
					} else {
						atualizaInimigos(&inimigos, jogador1);
						atualizaChefao(chefao1, jogador1);
						if(chefao1->vida <= 0){
							while(jogo != 1){
								al_wait_for_event(queue, &event);
								al_clear_to_color(al_map_rgb(0, 0, 0));
								al_draw_text(fontTTF, al_map_rgb(12, 238, 26), X_TELA / 2 - 75, Y_TELA / 2 - 15, 0, "CHEFE DERROTADO!");
								al_draw_text(fontTTF, al_map_rgb(12, 238, 26), X_TELA / 2 - 150, Y_TELA / 2, 0, "PRESSIONE ESPACO PARA SAIR");
								al_flip_display();
								if ((event.type == 10 && event.keyboard.keycode == 75) || (event.type == 42)) jogo = 1;
							}
						}
					}
				
					/*Pontos jogador*/
					sprintf(pontos, "SCORE: %d", jogador1->pontos);
					al_draw_text(fontTTF, al_map_rgb(12, 238, 26), 10, 10, 0, pontos);
				
					/*Vida jogador*/
					sprintf(pontos, "VIDA: %d", jogador1->vida);
					al_draw_text(fontTTF, al_map_rgb(12, 238, 26), 10, 30, 0, pontos);

	        		vivo = veMortePVE(jogador1);
            
					/*Desenha inimigos e seus tiros*/
					desenhaInimigos(inimigos);
            		balasInimigos(inimigos);


					/*Desenha jogador1*/
					if(jogador1->face == DIRECAO_ESQUERDA) al_draw_bitmap(jogadorEsquerda, jogador1->x - 24, jogador1->y - 24, 0);
					if(jogador1->face == DIRECAO_DIREITA) al_draw_bitmap(jogadorDireita, jogador1->x - 24, jogador1->y - 24, 0);
					if(jogador1->face == DIRECAO_CIMA) al_draw_bitmap(jogadorCima, jogador1->x - 24, jogador1->y - 24, 0);
					if(jogador1->face == DIRECAO_BAIXO) al_draw_bitmap(jogadorBaixo, jogador1->x - 24, jogador1->y - 24, 0);
 
		   			/*Desenha balas do jogador1*/
            		for (bala *id = jogador1->arma->tiros; id != NULL; id = (bala*) id->prox) {
                		al_draw_filled_circle(id->x, id->y, 2, al_map_rgb(255, 0, 0));
            		}
	            	if (jogador1->arma->tempo) jogador1->arma->tempo--;
    	        
    	        	al_flip_display();
        		}
        		else if ((event.type == 10) || (event.type == 12)) {
            		if (event.keyboard.keycode == 1) controleEsquerda(jogador1->controle);
	            	else if (event.keyboard.keycode == 4) controleDireita(jogador1->controle);
    	        	else if (event.keyboard.keycode == 23) controleCima(jogador1->controle);
	    	        else if (event.keyboard.keycode == 19) controleBaixo(jogador1->controle);
    		        else if (event.keyboard.keycode == 3) controleAtira(jogador1->controle);
       			}
	        	else if (event.type == 42) break;
			}
		} else if(modoJogo == 2) {/*Fse3/PVP*/
			if (p1k || p2k) {
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
            	al_clear_to_color(al_map_rgb(0, 0, 0));
				
				/*Desliza a tela*/
				al_draw_bitmap(fundo2, posicaoFundo, 0, 0);
				al_draw_bitmap(fundo2, posicaoFundo + larguraFundo, 0, 0);

				atualizaPosicao(jogador1, jogador2);
				
	            p1k = veMortePVP(jogador2, jogador1);
    	        p2k = veMortePVP(jogador1, jogador2);

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
 
		   		/*Desenha balas do jogador1*/
            	for (bala *id = jogador1->arma->tiros; id != NULL; id = (bala*) id->prox) {
                	al_draw_filled_circle(id->x, id->y, 2, al_map_rgb(255, 0, 0));
            	}
	            if (jogador1->arma->tempo) jogador1->arma->tempo--;
    	        
				/*Desenha balas do jogador2*/
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
		} else if(modoJogo == -1){
			al_clear_to_color(al_map_rgb(0, 0, 0));
			al_draw_text(fontTTF, al_map_rgb(12, 238, 26), X_TELA / 2 - 75, Y_TELA / 2 - 15, 0, "CHEFE DERROTADO!");
			al_draw_text(fontTTF, al_map_rgb(12, 238, 26), X_TELA / 2 - 150, Y_TELA / 2, 0, "PRESSIONE ESPACO PARA JOGAR NOVAMENTE");
			al_draw_text(fontTTF, al_map_rgb(12, 238, 26), X_TELA / 2, Y_TELA / 2 + 15, 0, "OU");
			al_draw_text(fontTTF, al_map_rgb(12, 238, 26), X_TELA / 2 - 110, Y_TELA / 2 + 30, 0, "PRESSIONE ESC PARA VOLTAR");
		}
	}

	/*100% de vida*/
	al_destroy_bitmap(jogadorBaixo);
	al_destroy_bitmap(jogadorCima);
	al_destroy_bitmap(jogadorDireita);
	al_destroy_bitmap(jogadorEsquerda);
	/*75% de vida*/
	al_destroy_bitmap(jogador75Baixo);
	al_destroy_bitmap(jogador75Cima);
	al_destroy_bitmap(jogador75Direita);
	al_destroy_bitmap(jogador75Esquerda);
	/*50% de vida*/
	al_destroy_bitmap(jogador50Baixo);
	al_destroy_bitmap(jogador50Cima);
	al_destroy_bitmap(jogador50Direita);
	al_destroy_bitmap(jogador50Esquerda);
	/*25% de vida*/
	al_destroy_bitmap(jogador25Baixo);
	al_destroy_bitmap(jogador25Cima);
	al_destroy_bitmap(jogador25Direita);
	al_destroy_bitmap(jogador25Esquerda);
	
	al_destroy_font(fontTTF);
	al_destroy_display(disp);
	al_destroy_timer(timer);
	al_destroy_event_queue(queue);
	destroiJogador(jogador1);
	destroiJogador(jogador2);
	return 0;
}