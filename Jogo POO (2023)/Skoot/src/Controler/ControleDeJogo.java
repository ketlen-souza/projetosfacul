package Controler;

import Characters.Personagem;
import Characters.Coletaveis;
import Characters.Skoot;
import Characters.Wall;
import Characters.Setas;
import auxiliar.Posicao;
import java.util.ArrayList;

public class ControleDeJogo {
    public void desenhaTudo(ArrayList<Personagem> e){
        for(int i = 0; i < e.size(); i++)
            e.get(i).autoDesenho();
    }
    
    public void processaTudo(ArrayList<Personagem> umaFase){
        Skoot skoot = (Skoot)umaFase.get(0);
        Personagem pIesimoPersonagem;
        
        //  Processamento da posicao do skoot
        for(int i = 0; i < umaFase.size(); i++){
            pIesimoPersonagem = umaFase.get(i);
            if(skoot.getPosicao().igual(pIesimoPersonagem.getPosicao())){
                if(pIesimoPersonagem.getClass() == Wall.class)
                    skoot.getPosicao().volta();
                else if(pIesimoPersonagem.isbTransponivel() && pIesimoPersonagem.isbRemovivel())           
                    umaFase.remove(pIesimoPersonagem);
                else if(pIesimoPersonagem.getClass() == Setas.class)
                    ((Setas)pIesimoPersonagem).setaEmpurra(skoot);
            }
        }
                
        //  Processamento das setas
        for(int i = 0; i < umaFase.size(); i++){
            pIesimoPersonagem = umaFase.get(i);
            if(pIesimoPersonagem.getClass() != Setas.class)
                continue;
            
            else if(!posicaoLivre(umaFase, pIesimoPersonagem)){
                Personagem pPersonagem = mesmaPosicao(umaFase, pIesimoPersonagem);           
                ((Setas)pIesimoPersonagem).setaEmpurra(pPersonagem);
            }
        }
        
        //  Movimenta o que esta em cima das setas
        for(int i = 0; i < umaFase.size(); i++){
            pIesimoPersonagem = umaFase.get(i);
            if(pIesimoPersonagem.getClass() == Setas.class)
                ((Setas)pIesimoPersonagem).setaEmpurra();
        }
    }
    
    //  Verifica se o skoot sera morto
    public boolean ehPosicaoMortal(ArrayList<Personagem> umaFase, Posicao p){
        Personagem pIesimoPersonagem;
        for(int i = 1; i < umaFase.size(); i++){
            pIesimoPersonagem = umaFase.get(i);
            if(pIesimoPersonagem.getPosicao().igual(p)) {
                if(pIesimoPersonagem.isbMortal()){
                    umaFase.remove(pIesimoPersonagem);
                    return false;
                }
                return true; 
            }
        }
        
        return true;
    }
    
    //  Verifica se ainda existe algum item coletável na fase 
    public boolean existeColetaveis(ArrayList<Personagem> umaFase){
        Personagem pIesimoPersonagem;
        int coletaveis = 0;
        for(int i = 1; i < umaFase.size(); i++){
            pIesimoPersonagem = umaFase.get(i);            
            if(pIesimoPersonagem.getClass() == Coletaveis.class)
                coletaveis++;
        }
        if(coletaveis == 0){
            return false;
        }
        return true;
    }
    
    //  Retorna true se a posicao p é válida para Skoot com relacao a todos os personagens no array
    public boolean ehPosicaoValida(ArrayList<Personagem> umaFase, Posicao p, String direcao){
        if(p.getLinha() < 1 || p.getLinha() > 11 || p.getColuna() < 1 || p.getColuna() > 11)
            return false;

        Personagem pIesimoPersonagem;
        for(int i = 1; i < umaFase.size(); i++){
            pIesimoPersonagem = umaFase.get(i);            
            if(!pIesimoPersonagem.isbTransponivel()){
                if(pIesimoPersonagem.getPosicao().igual(p)){
                    if(pIesimoPersonagem.isbMovivel()){
                    switch (direcao){
                        case "CIMA":
                            pIesimoPersonagem.moveUp();
                            if(posicaoLivre(umaFase,pIesimoPersonagem))
                               break;
                            
                            else{
                                if(pIesimoPersonagem.isbRemovivel())
                                    umaFase.remove(pIesimoPersonagem);
                                else {
                                    pIesimoPersonagem.getPosicao().volta();
                                    return false;
                                }
                            }
                            break;
                            
                        case "BAIXO":
                            pIesimoPersonagem.moveDown();
                            if(posicaoLivre(umaFase,pIesimoPersonagem))
                                break;
                            
                            else{
                                if(pIesimoPersonagem.isbRemovivel())
                                    umaFase.remove(pIesimoPersonagem);
                                else {
                                    pIesimoPersonagem.getPosicao().volta();
                                    return false;
                                }
                            }
                            break;
                            
                        case "ESQUERDA":
                            pIesimoPersonagem.moveLeft();
                            if(posicaoLivre(umaFase,pIesimoPersonagem))
                                break;
                            
                            else{
                                if(pIesimoPersonagem.isbRemovivel())
                                    umaFase.remove(pIesimoPersonagem);
                                else {
                                    pIesimoPersonagem.getPosicao().volta();
                                    return false;
                                }
                            }
                            break;
                            
                        case "DIREITA":
                            pIesimoPersonagem.moveRight();
                            if(posicaoLivre(umaFase,pIesimoPersonagem))
                               break;
                            
                            else{
                                if(pIesimoPersonagem.isbRemovivel())
                                    umaFase.remove(pIesimoPersonagem);
                                else {
                                    pIesimoPersonagem.getPosicao().volta();
                                    return false;
                                }
                            }
                            break;    
                            
                        }
                    return true;
                    }
                 return false;
                }
            }
        }
        return true;
    }
    
    //  Verifica se a posicao em questao esta ocupada
    public boolean posicaoLivre(ArrayList<Personagem> umaFase, Personagem pPersonagem){
        if(pPersonagem.getPosicao().getLinha() < 1 || pPersonagem.getPosicao().getLinha() > 11 || pPersonagem.getPosicao().getColuna() < 1 || pPersonagem.getPosicao().getColuna() > 11)
            return false;
        
        Personagem pIesimoPersonagem;
        for(int i = 1; i < umaFase.size(); i++){
            pIesimoPersonagem = umaFase.get(i);
            if(pIesimoPersonagem == pPersonagem)
                continue;
            if(pIesimoPersonagem.getPosicao().igual(pPersonagem.getPosicao()))
                if(!pIesimoPersonagem.isbMovivel() || !pIesimoPersonagem.isbTransponivel() || !pIesimoPersonagem.isbRemovivel())
                    return false;
        }        
        return true;
    }
    
    //  Retorna um personagem que esta na mesma posicao que outro
    public Personagem mesmaPosicao(ArrayList<Personagem> umaFase, Personagem pPersonagem){
        Personagem pIesimoPersonagem;
        pIesimoPersonagem = umaFase.get(0);
        for(int i = 1; i <= umaFase.size(); i++){
            if(pIesimoPersonagem == pPersonagem)
                continue;
            if(pIesimoPersonagem.getPosicao().igual(pPersonagem.getPosicao()))
                break;
            pIesimoPersonagem = umaFase.get(i);
        }
        return pIesimoPersonagem;
    }
}
