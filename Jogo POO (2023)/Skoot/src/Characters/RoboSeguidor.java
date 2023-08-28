package Characters;

import Auxiliar.Consts;
import Auxiliar.Desenho;
import auxiliar.Posicao;
import java.util.Random;

public class RoboSeguidor extends Personagem{
    private int iContaIntervalos;
    private int iDirecaoAtual;
    private Posicao pPosicaoSkoot;

    private static final int DIREITA = 0;
    private static final int ESQUERDA = 1;
    private static final int BAIXO = 2;
    private static final int CIMA = 3;
    
    public RoboSeguidor(String sNomeImagePNG, Posicao pPosicaoSkoot) {
        super(sNomeImagePNG);
        super.bMovivel = false;         // pode ser empurrado
        super.bQuebravel = false;       // quebrado quando clicado
        super.bMortal = true;           // mata o skoot
        super.bTransponivel = false;    // pode ser atravessado
        this.iContaIntervalos = 0;
        this.pPosicaoSkoot = pPosicaoSkoot;
    }

    public void autoDesenho(){
        super.autoDesenho();
        this.iContaIntervalos++;
        
        if(this.iContaIntervalos == Consts.TIMER/2){
            this.iContaIntervalos = 0;

            Posicao pPosicaoRobo = super.getPosicao();
            Random rand = new Random();
            boolean xOuY = rand.nextBoolean();  //  Aleatoriza entre linha e coluna, qual a proxima direcao em que ira                 
            boolean valido = false;

            int antiLoop = 0;   //  Impede casos de loop infinito quando o robo esta preso
            
            //  Logica usada para perseguir o skoot
            while(!valido && antiLoop < 20){
                if (xOuY) {
                    int difLinha = pPosicaoSkoot.getLinha() - pPosicaoRobo.getLinha();
                    if (difLinha < 0 && super.moveUp() && validaPosicao())
                        valido = true;
                    else if (difLinha > 0 && super.moveDown() && validaPosicao())
                        valido = true;                        
                    else
                        xOuY = !xOuY;

                } else {
                    int difColuna = pPosicaoSkoot.getColuna() - pPosicaoRobo.getColuna();
                    if (difColuna < 0 && super.moveLeft() && validaPosicao())
                        valido = true;                        
                    else if (difColuna > 0 && super.moveRight() && validaPosicao())
                        valido = true;                        
                    else
                        xOuY = !xOuY;
                }
                antiLoop++;
            } 
            
            //  Movimento aleatorio,caso perseguir o skoot nao seja viavel
            if(!valido && antiLoop == 20){
                do {
                    iDirecaoAtual = rand.nextInt(4);                    

                    if(iDirecaoAtual == DIREITA)
                        super.moveRight();
                    else if(iDirecaoAtual == ESQUERDA)
                        super.moveLeft();
                    else if(iDirecaoAtual == BAIXO)
                        super.moveDown();
                    else if(iDirecaoAtual == CIMA)
                        super.moveUp();
                    antiLoop++;
                } while(!validaPosicao() && antiLoop < 40);
            }
        }
    }

    private boolean validaPosicao(){
        if (!Desenho.acessoATelaDoJogo().posicaoLivre(this)){
            this.pPosicao.volta();
            return false;
        }
        return true;       
    }
}

