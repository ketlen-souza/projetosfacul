package Characters;

import java.io.Serializable;

public class Coletaveis extends Personagem implements Serializable {

    public Coletaveis(String sNomeImagePNG) {
        super(sNomeImagePNG);
        super.bRemovivel = true;        // some se passar por cima
        super.bTransponivel = true;     // pode ser atravessado
    }
    
    public void autoDesenho() {
        super.autoDesenho();
    }    
    
}
