package lms.controller;
import lms.model.facade.LMSModel;
import lms.view.*;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class GridDisplayPanelListener implements ActionListener {
   private GridDisplayPanel gridPanel;
   private LMSMainView view;
   private LMSModel model;

   public GridDisplayPanelListener(GridDisplayPanel gridPanel) {
       
       // the following 3 lines result in a complete "chain" that allows you to: 
       // 1) invoke the Model by calling model.doSomething(...); 
       // 2) access/update "gridPanel" or any other sub-view by calling view.getSomeSubview();
       this.gridPanel = gridPanel;
       this.view = gridPanel.getMainView(); 
       this.model = view.getModel();        
   }

   public void actionPerformed(ActionEvent actionEvent) {
       // find out which component was selected HINT: use "gridPanel" reference
       // invoke the model
       // update the view     
 
   }

   
}
