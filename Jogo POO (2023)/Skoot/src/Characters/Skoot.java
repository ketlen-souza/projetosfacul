package Characters;

import Auxiliar.Desenho;
import java.io.Serializable;

public class Skoot extends Personagem implements Serializable{
    public Skoot(String sNomeImagePNG) {
        super(sNomeImagePNG);
        super.bMovivel = true;         // pode ser empurrado
        super.bQuebravel = false;       // quebrado quando clicado
        super.bMortal = false;           // mata o skoot
        super.bTransponivel = false;    // pode ser atravessado

    }

    public void voltaAUltimaPosicao(){
        this.pPosicao.volta();
    }
    
    public boolean setPosicao(int linha, int coluna){
        if(this.pPosicao.setPosicao(linha, coluna)){
            if (!Desenho.acessoATelaDoJogo().ehPosicaoValida(this.getPosicao())) {
                this.voltaAUltimaPosicao();
            }
            return true;
        }
        return false;       
    }

    private boolean validaPosicao(){
        if (!Desenho.acessoATelaDoJogo().ehPosicaoValida(this.getPosicao())) {
            this.voltaAUltimaPosicao();
            return false;
        }
        return true;       
    }
    
    public boolean moveUp() {
        if(super.moveUp())
            return validaPosicao();
        return false;
    }

    public boolean moveDown() {
        if(super.moveDown())
            return validaPosicao();
        return false;
    }

    public boolean moveRight() {
        if(super.moveRight())
            return validaPosicao();
        return false;
    }
    
    public boolean moveLeft() {
        if(super.moveLeft())
            return validaPosicao();
        return false;
    } 
    
    public void autoDesenho(){
        super.autoDesenho();
    }
}
