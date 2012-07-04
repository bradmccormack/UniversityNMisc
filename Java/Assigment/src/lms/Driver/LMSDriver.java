package lms.Driver;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;

import javax.swing.JOptionPane;

import lms.controller.MainViewListener;
import lms.model.*;
import lms.view.*;
import lms.model.facade.*;

public class LMSDriver {

 
   /**
    * @param args
    */
   public static void main(String[] args) {
      try {
         
         // initialize the  model
         final LMSModel model = new LMSFacade();
         
         // create the view
         final LMSMainView mainView = new LMSMainView(model);

         /*get the screen width and height and make it a percentage later !!*/
         mainView.setLocationByPlatform(true);
         mainView.setSize(1024, 768);

         mainView.addWindowListener(new WindowAdapter() {
             @Override
            public void windowClosing(WindowEvent e) {
                int reply=JOptionPane.showConfirmDialog(mainView, "Are you sure you want to quit?","Quit LMS System OUA 2010 Term 2?",JOptionPane.YES_NO_OPTION);
                if(reply==JOptionPane.NO_OPTION) 
                   mainView.setDefaultCloseOperation(mainView.DO_NOTHING_ON_CLOSE);
                else
                   System.exit(0);
             }
         });
         
         //For testing to get the grid working - REMOVE ME LATER
         model.addCollection(new LibraryCollection("IT","Information Technology"));
         
         
         int holdingcode;
         for(holdingcode=0;holdingcode<3;holdingcode++)
        	 model.addHolding(new Book( holdingcode++,"Book I AM A VERY VERY VERY VERY VERY VERY VERY LONG NAME "+holdingcode));
         
         for(holdingcode=3;holdingcode<9;holdingcode++)
        	 model.addHolding(new Video( holdingcode++,"Video I AM A VERY VERY VERY VERY VERY VERY VERY LONG NAME "+holdingcode,8));
         

         mainView.getGrid().setHoldings(model.getAllHoldings());
         mainView.setVisible(true);
         
         
     } catch (Exception exp) {
       //
     }

   }

}
