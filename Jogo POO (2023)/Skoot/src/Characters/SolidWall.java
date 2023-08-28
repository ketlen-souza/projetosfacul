package Characters;

import java.io.Serializable;
import Auxiliar.Consts;
import auxiliar.Posicao;
import java.awt.Graphics;
import java.awt.Image;
import java.awt.image.BufferedImage;
import java.io.IOException;
import javax.swing.ImageIcon;

public class SolidWall extends Wall implements Serializable{
    protected ImageIcon iImage;
    
    public SolidWall(String sNomeImagePNG, boolean bQuebravel) {
        super(sNomeImagePNG);
        super.bMovivel = false;         // pode ser empurrado
        super.bQuebravel = bQuebravel;  // quebrado quando clicado
        super.bMortal = false;          // mata o skoot
        super.bTransponivel = false;    // pode ser atravessado
        super.bRemovivel = false;       // some se passar por cima
        
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
