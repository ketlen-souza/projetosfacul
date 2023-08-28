package Characters;

import Characters.Personagem;

public class Setas extends Personagem {
    private String tipoSeta;
    private Personagem personagemEmpurrado;
    
    public Setas(String sNomeImagePNG) {
        super(sNomeImagePNG);
        this.tipoSeta = sNomeImagePNG;
        super.bMortal = false;      // mata o skoot
        super.bTransponivel = true; // pode passar por cima
        super.bMovivel = false;      // pode ser empurrado
        super.bQuebravel = false;   // some se for clicado
        super.bRemovivel = false;   // some se passar por cima
    }
    
    public void autoDesenho() {
        super.autoDesenho();
    }
    
    public void setaEmpurra(Personagem pPersonagem){
        this.personagemEmpurrado = pPersonagem;
    }
    
    public void setaEmpurra(){
        if(personagemEmpurrado != null && personagemEmpurrado.getClass() != Setas.class){
            switch (tipoSeta) {
                case "upArrow.jpg":
                    this.personagemEmpurrado.moveUp();
                    break;
                case "downArrow.jpg":
                    this.personagemEmpurrado.moveDown();
                    break;
                case "leftArrow.jpg":
                    this.personagemEmpurrado.moveLeft();
                    break;
                case "rightArrow.jpg":
                    this.personagemEmpurrado.moveRight();
                    break;
            }
            personagemEmpurrado.autoDesenho();
        }
        personagemEmpurrado = null;
    }

    public boolean moveUp(){
        return false;
    }
    
    public boolean moveDown(){
        return false;
    }
    
    public boolean moveRight(){
        return false;
    }
    
    public boolean moveLeft(){
        return false;
    }
}