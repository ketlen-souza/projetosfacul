package Characters;

import java.io.Serializable;
import Auxiliar.Consts;
import java.awt.Graphics;
import java.awt.Image;
import java.awt.image.BufferedImage;
import java.io.IOException;
import javax.swing.ImageIcon;

public class MovableWall extends Wall implements Serializable{
    protected ImageIcon iImage;
    
    public MovableWall(String sNomeImagePNG, boolean bQuebravel, Skoot skoot) {
        super(sNomeImagePNG);
        super.bTransponivel = false;    // pode passar por cima
        super.bMortal = false;          // mata o skoot
        super.bMovivel = true;          // pode ser empurrado
        super.bRemovivel = false;       // some se passar em cima
        super.bQuebravel = bQuebravel;  // some se clicado
        
        try {
            iImage = new ImageIcon(new java.io.File(".").getCanonicalPath() + Consts.PATH + sNomeImagePNG);
            Image img = iImage.getImage();
            BufferedImage bi = new BufferedImage(Consts.CELL_SIDE, Consts.CELL_SIDE, BufferedImage.TYPE_INT_ARGB);
            Graphics g = bi.createGraphics();
            g.drawImage(img, 0, 0, Consts.CELL_SIDE, Consts.CELL_SIDE, null);
            iImage = new ImageIcon(bi);
        } catch (IOException ex) {
            System.out.println(ex.getMessage());
        }
    }
    

    public void autoDesenho() {
        super.autoDesenho();
    }
}