package Controler;

import java.lang.reflect.InvocationTargetException;
import Auxiliar.Consts;
import Characters.Personagem;
import Characters.RoboAleatorio;
import Characters.RoboSeguidor;
import Characters.Skoot;
import Characters.Wall;
import Characters.SolidWall;
import Characters.MovableWall;
import Characters.Coletaveis;
import Characters.Setas;
import java.util.ArrayList;

public class Fases {
    private ArrayList<Personagem> faseAtual;
    private Skoot skoot;
    private String sImageBackground;

    //      ARROWS
    private static final String DIREITA = "rightArrow.jpg";
    private static final String ESQUERDA = "leftArrow.jpg";
    private static final String CIMA = "upArrow.jpg";
    private static final String BAIXO = "downArrow.jpg";
    
    public Fases(Skoot skoot) {
        faseAtual = new ArrayList<Personagem>();
        this.skoot = skoot;
    }
    
    public void constroiFase(int fase){
        //  Insercao das bordas pretas
        desenhaBordas();

        if(fase == 1){
            sImageBackground = "backgroundFase1.jpg";
            fase1();
        }
        else if(fase == 2){
            sImageBackground = "backgroundFase2.jpg";
            fase2();
        }
        else if(fase == 3){
            sImageBackground = "backgroundFase3.jpg";
            fase3();
        }
        else if(fase == 4){
            sImageBackground = "backgroundFase4.jpg";
            fase4();
        }
        else if(fase == 5){
            sImageBackground = "backgroundFase5.jpg";
            fase5();
        }
        else if(fase == 6){
            sImageBackground = "backgroundFase6.jpg";
            fase6();
        }
    }
    
    private void fase1(){
        skoot.setPosicao(5, 5);
        
        //  Insercao dos itens coletaveis
        int[] lColetaveis = {1,11,1,11};
        int[] cColetaveis = {1,1,11,11};
        String[] tipoColetaveis = {"coletavel1.png", "coletavel2.png", "coletavel3.png", "coletavel4.png"};
        setCharacter(lColetaveis, cColetaveis, tipoColetaveis, Coletaveis.class);
        
        //  Insercao de 3 robos com movimentos aleatorios e um perseguidor
        int[] lRobos = {3, 1, 11};
        int[] cRobos = {1, 10, 10};
        String[] corRobos = {"yellowBot.png", "pinkBot.png", "greenBot.png"};
        setCharacter(lRobos, cRobos, corRobos, RoboAleatorio.class);
        
        RoboSeguidor R = new RoboSeguidor("blueBot.png", skoot.getPosicao());
        R.setPosicao(11, 2);
        this.addPersonagem(R);
        
        
        //  Insercao das paredes vermelhas
        for(int i = 2; i < 11; i += 2)
            for(int j = 2; j < 11; j += 2)
                setWalls(i, j, "staticRedWall.jpg", false, SolidWall.class);

        
        //  Insercao das paredes verdes
        int[] linhas = {1,1,2,2,2,3,3,4,4,5,5,6,6,7,7,8,8,9,9,10,10,10,10,11};
        int[] colunas = {2,6,3,9,11,2,6,1,9,2,10,3,7,6,8,9,11,4,10,1,3,7,9,8};
        for(int i = 0; i < linhas.length; i++)
            setWalls(linhas[i], colunas[i], "movingGreenWall.jpg", true, MovableWall.class);

    }
    
    private void fase2(){
        skoot.setPosicao(6, 6);
        
        
        //  Inserção das paredes vermelhas 
        int[] positions = {2, 4, 6, 8, 10};
        for (int i : positions) {
            setWalls(i, 4, "staticRedWall.jpg", false, SolidWall.class);
            setWalls(i, 8, "staticRedWall.jpg", false, SolidWall.class);
            setWalls(4, i, "staticRedWall.jpg", false, SolidWall.class);
            setWalls(8, i, "staticRedWall.jpg", false, SolidWall.class);
        }
        
        
        //  Insercao dos itens coletaveis
        int[] lColetaveis = {2,6,6,10};
        int[] cColetaveis = {6,2,10,6};
        String[] tipoColetaveis = {"coletavel1.png", "coletavel2.png", "coletavel3.png", "coletavel4.png"};
        setCharacter(lColetaveis, cColetaveis, tipoColetaveis, Coletaveis.class);
        
        
        //  Insercao de 3 robos com movimentos aleatorios e um perseguidor
        int[] lRobos = {2,10,10,2};
        int[] cRobos = {2,2,10,10};
        String[] corRobos = {"yellowBot.png", "pinkBot.png", "greenBot.png","blueBot.png"};
        setCharacter(lRobos, cRobos, corRobos, RoboAleatorio.class);
        
        
        //  Insercao das setas
        int[] lArrows = {1, 1, 3, 3, 3, 3, 3, 4, 4, 4, 4, 4, 4, 5, 5, 5, 5, 5, 5, 6, 7, 7, 7, 8, 8, 8, 8, 8, 8, 9, 9, 11, 11};
        int[] cArrows = {4, 8, 4, 5, 6, 7, 8, 1, 3, 5, 7, 9, 11, 1, 4, 8, 9, 10, 11, 1, 1, 4, 8, 1, 3, 5, 7, 9, 11, 4, 8, 4, 8};
        String[] images = {DIREITA, DIREITA, DIREITA, BAIXO, ESQUERDA, ESQUERDA, ESQUERDA, CIMA, BAIXO, BAIXO, CIMA, CIMA, BAIXO, CIMA, DIREITA, DIREITA, CIMA, ESQUERDA, ESQUERDA, CIMA, CIMA, DIREITA, ESQUERDA, CIMA, BAIXO, BAIXO, CIMA, CIMA, CIMA, DIREITA, DIREITA, ESQUERDA, DIREITA};
        for(int i = 0; i < images.length; i++){
                Setas A = new Setas(images[i]);
                A.setPosicao(lArrows[i], cArrows[i]);
                this.addPersonagem(A);
             }
         }
    
    private void fase3(){
        skoot.setPosicao(6, 6);
        
        //  Inserção das paredes vermelhas 
        for (int i = 2; i < Consts.RES - 2; i++) {
            setWalls(2, i, "movingRedWall.jpg", false, MovableWall.class);
            setWalls(Consts.RES - 3, i, "movingRedWall.jpg", false, MovableWall.class);
            if (i >= 4 && i <= Consts.RES - 5) {
                setWalls(4, i, "movingRedWall.jpg", false, MovableWall.class);
                setWalls(Consts.RES - 5, i, "movingRedWall.jpg", false, MovableWall.class);
            }
        }
        
        for (int i = 3; i < Consts.RES - 3; i++) {
            setWalls(i, 2, "movingRedWall.jpg", false, MovableWall.class);
            setWalls(i, Consts.RES - 3, "movingRedWall.jpg", false, MovableWall.class);
            if (i > 4 && i < Consts.RES - 5) {
                setWalls(i, 4, "movingRedWall.jpg", false, MovableWall.class);
                setWalls(i, Consts.RES - 5, "movingRedWall.jpg", false, MovableWall.class);
            }
        }
        

        //  Insercao dos itens coletaveis
        int[] linha = {6,6,6,6};
        int[] coluna = {1,3,9,11};
        String[] tipoColetaveis = {"coletavel1.png", "coletavel2.png", "coletavel3.png", "coletavel4.png"};
        setCharacter(linha, coluna, tipoColetaveis, Coletaveis.class);

        
        //  Insercao de 4 robos com movimentos aleatorios
        String[] corRobos = {"yellowBot.png", "pinkBot.png", "blueBot.png", "greenBot.png"};
        setCharacter(coluna, linha, corRobos, RoboAleatorio.class);
        
    }
    
    private void fase4(){
        skoot.setPosicao(5, 6);
        
        
        //  Insercao das paredes verdes estaticas
        for(int i = 2; i < 10; i += 2){
            for(int j = 2; j < 10; j += 2){
                setWalls(i, j, "staticGreenWall.jpg", true, SolidWall.class);
                setWalls(i+1, j+1, "staticGreenWall.jpg", true, SolidWall.class);
            }
            setWalls(i, 10, "staticGreenWall.jpg", true, SolidWall.class);
            setWalls(10, i, "staticGreenWall.jpg", true, SolidWall.class);
        }
        setWalls(10, 10, "staticGreenWall.jpg", true, SolidWall.class);
        
        
        //  Insercao das paredes vermelhas estaticas
        int[] posicoes = {1,4,1,8,2,1,2,9,3,6,4,3,4,11,6,3,6,9,7,4,8,1,9,2,9,8,9,11,11,2};
        for(int i = 0; i < posicoes.length; i += 2)
            setWalls(posicoes[i], posicoes[i+1], "staticRedWall.jpg", false, SolidWall.class);
            
        
        //  Insercao dos itens coletaveis
        int[] lColetaveis = {1,1,11,11};
        int[] cColetaveis = {1,11,1,11};
        String[] tipoColetaveis = {"coletavel1.png", "coletavel2.png", "coletavel3.png", "coletavel4.png"};
        setCharacter(lColetaveis, cColetaveis, tipoColetaveis, Coletaveis.class);
        
        
        //  Insercao de 3 robos com movimentos aleatórios e um perseguidor
        int[] lRobos = {1, 6, 11};
        int[] cRobos = {6, 11, 6};
        String[] corRobos = {"yellowBot.png", "greenBot.png", "blueBot.png"};
        setCharacter(lRobos, cRobos, corRobos, RoboAleatorio.class);
        
        RoboSeguidor R = new RoboSeguidor("pinkBot.png", skoot.getPosicao());
        R.setPosicao(6, 1);
        this.addPersonagem(R);
    }
    
    private void fase5(){
        skoot.setPosicao(3, 9);

        //  Insercao das paredes vermelhas estaticas
        int[] posicoes = {1,6,2,6,3,6,4,4,4,8,6,1,6,2,6,3,6,6,6,9,6,10,6,11,8,4,8,8,9,6,10,6,11,6};
        for(int i = 0; i < posicoes.length; i += 2)
            setWalls(posicoes[i], posicoes[i+1], "staticRedWall.jpg", false, SolidWall.class);
        
        
        //  Insercao das paredes vermelhas moveis
        int[] coordenadas = {8,10,10,8,10,10};
        for(int i = 0; i < coordenadas.length; i += 2)
            setWalls(coordenadas[i], coordenadas[i+1], "movingRedWall.jpg", false, MovableWall.class);

        
        //  Insercao dos itens coletaveis
        int[] lColetaveis = {1,5,7,11};
        int[] cColetaveis = {7,11,1,5};
        String[] tipoColetaveis = {"coletavel1.png", "coletavel2.png", "coletavel3.png", "coletavel4.png"};
        setCharacter(lColetaveis, cColetaveis, tipoColetaveis, Coletaveis.class);
  
        
        //  Insercao dos robos
        int[] lRobos = {1, 1, 2, 2};
        int[] cRobos = {1, 2, 1, 2};
        String[] corRobo = {"yellowBot.png", "blueBot.png", "pinkBot.png", "greenBot.png"};
        setCharacter(lRobos, cRobos, corRobo, RoboAleatorio.class);
        
        //  Insercao das setas
        int[] lArrows = {1, 2, 4, 4, 4, 5, 5, 5, 5, 5, 6, 6, 6, 6, 7, 7, 7, 7, 7, 8, 8, 8, 10, 11};
        int[] cArrows = {8, 7, 6, 7, 11, 4, 5, 6, 7, 10, 4, 5, 7, 8, 2, 5, 6, 7, 8, 1, 5, 6, 5, 4};
        String[] images = {BAIXO, BAIXO, BAIXO, ESQUERDA, ESQUERDA, DIREITA, BAIXO, DIREITA, CIMA, CIMA, CIMA, ESQUERDA, DIREITA, BAIXO, BAIXO, BAIXO, ESQUERDA, CIMA, ESQUERDA, BAIXO, DIREITA, CIMA, ESQUERDA, ESQUERDA};
        for(int i = 0; i < images.length; i++){
            Setas A = new Setas(images[i]);
            A.setPosicao(lArrows[i], cArrows[i]);
            this.addPersonagem(A);
        }
        
        //  Insercao dos blocos verdes em cima das setas (NAO FUNCIONANDO)
//        int[] blocos = {4, 6, 6, 4, 7, 5, 6, 7};
//        for(int i = 0; i < blocos.length; i += 2)
//            setWalls(blocos[i], blocos[i+1], "staticGreenWall.jpg", false, SolidWall.class);

    }
    
    private void fase6(){
        skoot.setPosicao(7, 5);
        desenhaBordas();
        
        //  Insercao das paredes vermelhas
        for(int i = 2; i < 11; i += 2){
            for(int j = 2; j < 11; j += 2){
                setWalls(i, j, "staticRedWall.jpg", false, SolidWall.class);
            }
        }
        
        
        //  Insercao dos coletaveis
        int[] lColetaveis = {3, 3, 9, 9};
        int[] cColetaveis = {3, 9, 3, 9};
        String[] tipoColetaveis = {"coletavel1.png", "coletavel2.png", "coletavel3.png", "coletavel4.png"};
        setCharacter(lColetaveis, cColetaveis, tipoColetaveis, Coletaveis.class);
        
        
        //  Insercao dos robos
        int[] lRobos = {3, 6, 6, 9};
        int[] cRobos = {6, 3, 9, 6};
        String[] corRobo = {"yellowBot.png", "blueBot.png", "pinkBot.png", "greenBot.png"};
        setCharacter(lRobos, cRobos, corRobo, RoboAleatorio.class);
        
        
        //  Insercao das setas
        String[] images = {CIMA, ESQUERDA, BAIXO, DIREITA, BAIXO, ESQUERDA, CIMA, ESQUERDA, CIMA, DIREITA, ESQUERDA, CIMA, 
            BAIXO, CIMA, BAIXO, DIREITA, CIMA, ESQUERDA, ESQUERDA, ESQUERDA, BAIXO, DIREITA, CIMA, ESQUERDA, 
            DIREITA, BAIXO, CIMA, ESQUERDA, BAIXO, DIREITA, DIREITA, DIREITA, 
            CIMA, ESQUERDA, BAIXO, DIREITA, CIMA, BAIXO, CIMA, DIREITA, BAIXO, DIREITA, CIMA, ESQUERDA, 
            BAIXO, BAIXO, CIMA, DIREITA, BAIXO, ESQUERDA, BAIXO, ESQUERDA, BAIXO, ESQUERDA, ESQUERDA, DIREITA};
        int cont = 0;
                
        for(int i = 2; i < 12; i += 2){
            for(int j = 1; j < 12; j += 2){
                if((j == 6 && (i == 3 || i == 9)) || (j == 3 && (i == 6 || i == 9)))
                    continue;
                if((i == 6 && (j == 3 || j == 9)) || (i == 3 && (j == 6 || j == 9)))
                    continue;
                
                setCharacter(i, j, images[cont], Setas.class);
                setCharacter(j, i, images[cont+1], Setas.class);
                cont += 2;
            }
        }
    }
    
    private <T extends Personagem> void setCharacter(int[] linha, int[] coluna, String[] imagem, Class<T> characterClass) {
        for (int i = 0; i < coluna.length; i++) {
            try {
                T character = characterClass.getDeclaredConstructor(String.class).newInstance(imagem[i]);
                character.setPosicao(linha[i], coluna[i]);
                this.addPersonagem(character);
            } catch (Exception e) {
                e.printStackTrace();
            }
        }
    }    
    
    private <T extends Personagem> void setCharacter(int linha, int coluna, String imagem, Class<T> characterClass) {
        try {
            T character = characterClass.getDeclaredConstructor(String.class).newInstance(imagem);
            character.setPosicao(linha, coluna);
            this.addPersonagem(character);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
    
    private <T extends Wall> void setWalls(int linha, int coluna, String image, boolean quebravel, Class<T> wallClass) {
        try {
            T wall;
            if (wallClass == MovableWall.class) {
                wall = wallClass.getDeclaredConstructor(String.class, boolean.class, Skoot.class)
                        .newInstance(image, quebravel, this.skoot);
            } else {
                wall = wallClass.getDeclaredConstructor(String.class, boolean.class)
                        .newInstance(image, quebravel);
            }

            wall.setPosicao(linha, coluna);
            this.addPersonagem(wall);
        } catch (InstantiationException | IllegalAccessException | NoSuchMethodException | InvocationTargetException e) {
            e.printStackTrace();
        }
    }

    private void addPersonagem(Personagem umPersonagem) {
        faseAtual.add(umPersonagem);
    }
    
    public ArrayList<Personagem> getFase(int i){
        return faseAtual;
    }
    
    public String getImageBackground(){
        return this.sImageBackground;
    }

    private void desenhaBordas(){
        for (int i = 0; i < Consts.RES; i++) {
            setWalls(i, 0, "blackBackground.png", false, SolidWall.class);
            setWalls(i, Consts.RES - 1, "blackBackground.png", false, SolidWall.class);

            if (i > 0 && i < Consts.RES - 1) {
                setWalls(0, i, "blackBackground.png", false, SolidWall.class);
                setWalls(Consts.RES - 1, i, "blackBackground.png", false, SolidWall.class);
            }
        }
    }
}
