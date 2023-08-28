package Characters;

import Auxiliar.Consts;
import Auxiliar.Desenho;
import java.util.Random;

public class RoboAleatorio extends Personagem{
    private int iContaIntervalos;
    private int iDirecaoAtual;
    
    private static final int DIREITA = 0;
    private static final int ESQUERDA = 1;
    private static final int BAIXO = 2;
    private static final int CIMA = 3;
    
    public RoboAleatorio(String sNomeImagePNG) {
        super(sNomeImagePNG);
        super.bMovivel = false;         // pode ser empurrado
        super.bQuebravel = false;       // quebrado quando clicado
        super.bMortal = true;           // mata o skoot
        super.bTransponivel = false;    // pode ser atravessado
        this.iContaIntervalos = 0;
    }
    
    public void autoDesenho(){
        super.autoDesenho();
        this.iContaIntervalos++;
        
        if(this.iContaIntervalos == Consts.TIMER/2){
            this.iContaIntervalos = 0;
            Random rand = new Random();
            int randomMove = rand.nextInt(5); // 20% de chance de ter um movimento aleatorio

            int stop = 0;   //  Impede casos de loop infinito quando o robo esta preso
            while(stop < 20){    
                if (randomMove == 0)
                    iDirecaoAtual = rand.nextInt(4);
                
                if(iDirecaoAtual == DIREITA && super.moveRight() && validaPosicao())
                    break;
                else if(iDirecaoAtual == ESQUERDA && super.moveLeft() && validaPosicao())
                    break;
                else if(iDirecaoAtual == BAIXO && super.moveDown() && validaPosicao())
                    break;
                else if(iDirecaoAtual == CIMA && super.moveUp() && validaPosicao())
                    break;
                
                if (randomMove != 0)
                    iDirecaoAtual = rand.nextInt(4);
                stop++;
            }
        }
    }

    private boolean validaPosicao(){
        if (!Desenho.acessoATelaDoJogo().posicaoLivre(this)) {
            this.pPosicao.volta();
            return false;
        }
        return true;       
    }
}

