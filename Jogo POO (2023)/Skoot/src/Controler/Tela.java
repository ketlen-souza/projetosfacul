package Controler;

import Characters.Personagem;
import Characters.Skoot;
import Controler.Fases;
import Auxiliar.Consts;
import Auxiliar.Desenho;
import auxiliar.Posicao;
import java.awt.Graphics;
import java.awt.Image;
import java.awt.Toolkit;
import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Timer;
import java.util.TimerTask;
import java.util.logging.Level;
import java.util.logging.Logger;
import java.io.FileOutputStream;
import java.io.ObjectOutputStream;
import java.io.FileInputStream;
import java.io.ObjectInputStream;

public class Tela extends javax.swing.JFrame implements MouseListener, KeyListener {

    private Skoot skoot;
    private int life = 5;
    private Fases level;
    private ArrayList<Personagem> faseAtual;
    private ControleDeJogo cj = new ControleDeJogo();
    private Graphics g2;
    private int nivelFase = 1;
    private String backgroundImage;

    public Tela() {
        Desenho.setCenario(this);
        initComponents();
        this.addMouseListener(this); /*mouse*/
        this.addKeyListener(this);   /*teclado*/
        /*Cria a janela do tamanho do tabuleiro + insets (bordas) da janela*/
        this.setSize(Consts.RES * Consts.CELL_SIDE + getInsets().left + getInsets().right, Consts.RES * Consts.CELL_SIDE + getInsets().top + getInsets().bottom);
            
        //  Adiciona o skoot na fase
        faseAtual = new ArrayList<Personagem>();
        skoot = new Skoot("skoot.png");
        this.addPersonagem(skoot);
        
        //  Constroi a fase e adiciona os demais personagens dela
        level = new Fases(skoot);
        level.constroiFase(this.nivelFase);
        this.addPersonagem(level.getFase(1));
        this.backgroundImage = level.getImageBackground();
    }

    public boolean ehPosicaoValida(Posicao p){
        return cj.ehPosicaoValida(this.faseAtual, p, p.getDirection());
    }
    
    public boolean ehPosicaoMotal(Posicao p){
        return cj.ehPosicaoMortal(this.faseAtual, p);
    }
    
    public boolean posicaoLivre(Personagem p){
        return cj.posicaoLivre(this.faseAtual, p);
    }
    
    public Personagem mesmaPosicao(Personagem p){
        return cj.mesmaPosicao(this.faseAtual, p);
    }
    
    public void addPersonagem(Personagem umPersonagem) {
        faseAtual.add(umPersonagem);
    }
    
    public void addPersonagem(ArrayList<Personagem> umPersonagem) {
        faseAtual.addAll(umPersonagem);
    }

    public void removePersonagem(Personagem umPersonagem) {
        faseAtual.remove(umPersonagem);
    }

    public Graphics getGraphicsBuffer(){
        return g2;
    }
    
    public void paint(Graphics gOld) {
        Graphics g = this.getBufferStrategy().getDrawGraphics();
        /*Criamos um contexto gráfico*/
        g2 = g.create(getInsets().left, getInsets().top, getWidth() - getInsets().right, getHeight() - getInsets().top);
        
        /*************Desenha cenário de fundo**************/
        for (int i = 0; i < Consts.RES; i++) {
            for (int j = 0; j < Consts.RES; j++) {
                try {
                    Image newImage = Toolkit.getDefaultToolkit().getImage(new java.io.File(".").getCanonicalPath() + Consts.PATH + backgroundImage);
                    g2.drawImage(newImage, j * Consts.CELL_SIDE, i * Consts.CELL_SIDE, Consts.CELL_SIDE, Consts.CELL_SIDE, null);

                } catch (IOException ex) {
                    Logger.getLogger(Tela.class.getName()).log(Level.SEVERE, null, ex);
                }
            }
        }
        
        desenhaVidas();

        if (!this.faseAtual.isEmpty()) {
            this.cj.processaTudo(faseAtual);
            this.cj.desenhaTudo(faseAtual);
            skoot.autoDesenho();
            desenhaVidas();
            
            if (!ehPosicaoMotal(skoot.getPosicao())) {
                this.life--;
                this.faseAtual.clear();
                skoot = new Skoot("skoot.png");
                this.addPersonagem(skoot);
                level = new Fases(skoot);
                level.constroiFase(this.nivelFase);
                this.addPersonagem(level.getFase(1));
                this.backgroundImage = level.getImageBackground();
            
            } else if (!this.cj.existeColetaveis(faseAtual) && this.nivelFase < 7){
                this.nivelFase++; 
                this.faseAtual.clear();
                this.addPersonagem(skoot);
                Fases level = new Fases(skoot);
                level.constroiFase(this.nivelFase);
                this.addPersonagem(level.getFase(1));
                this.skoot = (Skoot) faseAtual.get(0);
                this.backgroundImage = level.getImageBackground();
            }
            
            if(this.nivelFase > 6){
                try {
                    Image newImage = Toolkit.getDefaultToolkit().getImage(new java.io.File(".").getCanonicalPath() + Consts.PATH + "winCase.png");
                    g2.drawImage(newImage, 0, 0, Consts.RES * Consts.CELL_SIDE, Consts.RES * Consts.CELL_SIDE, null);
                } catch (IOException ex) {
                    Logger.getLogger(Tela.class.getName()).log(Level.SEVERE, null, ex);
                }
            }
            
            if(this.life < 1){
                try {
                    Image newImage = Toolkit.getDefaultToolkit().getImage(new java.io.File(".").getCanonicalPath() + Consts.PATH + "gameOver.png");
                    g2.drawImage(newImage, 0, 0, Consts.RES * Consts.CELL_SIDE, Consts.RES * Consts.CELL_SIDE, null);
                } catch (IOException ex) {
                    Logger.getLogger(Tela.class.getName()).log(Level.SEVERE, null, ex);
                }
            }          
        }
        
        g.dispose();
        g2.dispose();
        if (!getBufferStrategy().contentsLost()) {
            getBufferStrategy().show();
        }
    }

    public void go() {
        TimerTask task = new TimerTask() {
            public void run() {
                repaint();
            }
        };
        Timer timer = new Timer();
        timer.schedule(task, 0, Consts.PERIOD);
    }
    
    public void keyPressed(KeyEvent e) {
        if (e.getKeyCode() == KeyEvent.VK_C) 
            this.faseAtual.clear();
        
            //  Teclas que controlam o personagem Skoot
        else if (e.getKeyCode() == KeyEvent.VK_UP || e.getKeyCode() == KeyEvent.VK_W)
            skoot.moveUp();
        else if (e.getKeyCode() == KeyEvent.VK_DOWN || e.getKeyCode() == KeyEvent.VK_S)
            skoot.moveDown();
        else if (e.getKeyCode() == KeyEvent.VK_LEFT || e.getKeyCode() == KeyEvent.VK_A)
            skoot.moveLeft();
        else if (e.getKeyCode() == KeyEvent.VK_RIGHT || e.getKeyCode() == KeyEvent.VK_D)
            skoot.moveRight();
        
            //  Tecla que salva o jogo no momento atual em um arquivo
        else if (e.getKeyCode() == KeyEvent.VK_P)
            saveLevel(faseAtual, this.nivelFase, this.life, "currentLevel.txt");
        
            //  Tecla para carregar um jogo salvo em arquivo
        else if (e.getKeyCode() == KeyEvent.VK_L) {
            Object[] loading = loadLevel("currentLevel.txt");
            this.nivelFase = (int) loading[0];
            this.life = (int) loading[1];
            this.faseAtual = (ArrayList<Personagem>) loading[2];
            skoot = (Skoot) faseAtual.get(0);
            this.backgroundImage = level.getImageBackground();
            
            //  Tecla que reinicia a fase atual do zero (ou da primeira fase, caso finalize o jogo)
        } else if (e.getKeyCode() == KeyEvent.VK_R){
                this.faseAtual.clear();
                skoot = new Skoot("skoot.png");
                this.addPersonagem(skoot);
                level = new Fases(skoot);
            
                if(this.nivelFase > 6 || this.life < 1){    //  Reinicio de todo jogo ao chegar no final
                    nivelFase = 1;
                    this.life = 5;
                }
                
                level.constroiFase(this.nivelFase);
                this.addPersonagem(level.getFase(1));
                this.backgroundImage = level.getImageBackground();
        }
        
        this.setTitle("Skooter BSI");
        repaint(); /*invoca o paint imediatamente, sem aguardar o refresh*/
    }

    //  Remocao de uma parede quando clicada e quando o skoot esta adjacente a ela
    public void mousePressed(MouseEvent e) {
        /* Clique do mouse desligado*/
        int x = e.getX();
        int y = e.getY();

        this.setTitle("Skooter BSI");
        
        Posicao pPosicao = new Posicao(y/Consts.CELL_SIDE - 1, x/Consts.CELL_SIDE);
        Personagem pIesimoPersonagem;
        for(int i = 1; i < faseAtual.size(); i++){
            pIesimoPersonagem = faseAtual.get(i);
            if(pIesimoPersonagem.getPosicao().igual(pPosicao))
                if(skootProximo(pIesimoPersonagem))
                    if(pIesimoPersonagem.isbQuebravel())
                        faseAtual.remove(pIesimoPersonagem);
        }
        
        repaint();
    }
    
    public void desenhaVidas(){
        int vida = this.life;
        for (int i = 0; i < 5; i++) {
            try {
                Image newImage;
                if(vida > 0)
                    newImage = Toolkit.getDefaultToolkit().getImage(new java.io.File(".").getCanonicalPath() + Consts.PATH + "life.png");
                else 
                    newImage = Toolkit.getDefaultToolkit().getImage(new java.io.File(".").getCanonicalPath() + Consts.PATH + "death.png");
                
                g2.drawImage(newImage, (4 + i) * Consts.CELL_SIDE, 0 * Consts.CELL_SIDE, Consts.CELL_SIDE, Consts.CELL_SIDE, null);

            } catch (IOException ex) {
                Logger.getLogger(Tela.class.getName()).log(Level.SEVERE, null, ex);
            }
            vida--;
        }
    }
    
    //  Verifica se a posicao do skoot esta adjacente a posicao de um personagem especifico
    private boolean skootProximo(Personagem pPersonagem){
        int linhaSkoot = skoot.getPosicao().getLinha();
        int colunaSkoot = skoot.getPosicao().getColuna();
        int linhaPersonagem = pPersonagem.getPosicao().getLinha();
        int colunaPersonagem = pPersonagem.getPosicao().getColuna();
        
        if((linhaSkoot == linhaPersonagem && (colunaSkoot == colunaPersonagem + 1 || colunaSkoot == colunaPersonagem - 1)) 
                || (colunaSkoot == colunaPersonagem && (linhaSkoot == linhaPersonagem + 1 || linhaSkoot == linhaPersonagem - 1)))
            return true;
        return false;
    }
    
    //  Salvamento da fase no momento atual em um arquivo
    public static void saveLevel(ArrayList<Personagem> arrayList, int fase, int vidas, String nomeArquivo) {
        try {
            FileOutputStream fileOut = new FileOutputStream(nomeArquivo);
            ObjectOutputStream objectOut = new ObjectOutputStream(fileOut);
            objectOut.writeInt(fase); // Salva o numero da fase atual
            objectOut.writeInt(vidas); // Salva a quantidade de vidas que tinha
            objectOut.writeObject(arrayList);
            objectOut.close();
            System.out.println("A fase foi salva com sucesso");
        } catch (IOException e) {
            System.out.println("Erro ao salvar fase");
            e.printStackTrace();
        }
    }
    
    //  Recuparacao da fase salva no arquivo
    public static Object[] loadLevel(String nomeArquivo) {
        Object[] loadedLevel = new Object[3];
        try {
            FileInputStream fileIn = new FileInputStream(nomeArquivo);
            ObjectInputStream objectIn = new ObjectInputStream(fileIn);
            int fase = objectIn.readInt(); // Recupera o número inteiro primeiro
            int vidas = objectIn.readInt(); // Recupera o número inteiro primeiro
            ArrayList<Personagem> arrayList = (ArrayList<Personagem>) objectIn.readObject(); // Recupera a ArrayList em seguida
            objectIn.close();
            System.out.println("Fase recuperada");
            loadedLevel[0] = fase;
            loadedLevel[1] = vidas;
            loadedLevel[2] = arrayList;
        } catch (IOException | ClassNotFoundException e) {
            System.out.println("Erro ao recarregar fase");
            e.printStackTrace();
        }
        return loadedLevel;
    }
    
    // <editor-fold defaultstate="collapsed" desc="Generated Code">//GEN-BEGIN:initComponents
    private void initComponents() {

        setDefaultCloseOperation(javax.swing.WindowConstants.EXIT_ON_CLOSE);
        setTitle("POO2023-1 - Skooter");
        setAlwaysOnTop(true);
        setAutoRequestFocus(false);
        setResizable(false);

        javax.swing.GroupLayout layout = new javax.swing.GroupLayout(getContentPane());
        getContentPane().setLayout(layout);
        layout.setHorizontalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGap(0, 561, Short.MAX_VALUE)
        );
        layout.setVerticalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGap(0, 500, Short.MAX_VALUE)
        );

        pack();
    }// </editor-fold>//GEN-END:initComponents
    // Variables declaration - do not modify//GEN-BEGIN:variables
    // End of variables declaration//GEN-END:variables

    public void mouseMoved(MouseEvent e) {
    }

    public void mouseClicked(MouseEvent e) {
    }

    public void mouseReleased(MouseEvent e) {
    }

    public void mouseEntered(MouseEvent e) {
    }

    public void mouseExited(MouseEvent e) {
    }

    public void mouseDragged(MouseEvent e) {
    }

    public void keyTyped(KeyEvent e) {
    }

    public void keyReleased(KeyEvent e) {
    }
}
