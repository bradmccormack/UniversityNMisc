package lms.controller;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JOptionPane;

import lms.model.LibraryCollection;
import lms.model.facade.LMSModel;
import lms.view.LMSMainView;

public class MainViewListener implements ActionListener {

   private LMSMainView view;
   private LMSModel model;
   
   public MainViewListener(LMSMainView view)
   {
      this.view=view;
      this.model=this.view.getModel();
   }

   @Override
   public void actionPerformed(ActionEvent arg0) {
      String action=arg0.getActionCommand();
      String code,name;
      
      if(action.equals("New"))
      {
    	  //check for cancel in all input
    	  code=JOptionPane.showInputDialog("Enter a code for the new library collection");
    	  name=JOptionPane.showInputDialog("Enter a name for the Collection ");
    	  model.addCollection(new LibraryCollection(code,name));
    	  
    	  JOptionPane.showMessageDialog(this.view, "Collection created !");
    	  view.setCodeLabel(code);
    	  view.setVideoCount("0");
    	  view.setBookCount("0");
    	  
      }
      
      
   }

      
  
}
