package lms.view;
import java.awt.Color;
import java.awt.GridLayout;

import lms.controller.GridDisplayPanelListener;
import lms.model.Book;
import lms.model.Holding;

import javax.swing.BorderFactory;
import javax.swing.BoxLayout;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTextArea;
import javax.swing.border.Border;

public class GridDisplayPanel extends JPanel{
   private LMSMainView view;
   private GridDisplayPanelListener listener; // you should have one dedicated listener per sub-view!!!
   
   // ...declare all needed Swing components    
   // TODO
   
   public GridDisplayPanel (LMSMainView view) {
       this.view = view;            
       GridDisplayPanelListener listener = new GridDisplayPanelListener(this); // your sub-view is now "mapped" to a controller        
       // GUI stuff: initialise/add components, set layout manager, add listener as needed etc.    
   
   
    /*Set the layout of this to Grid*/   
   }
  
   // provide getters for the components as needed
  
   // provide methods for updating UI if needed
   public void setHoldings(Holding[] holdings)
   {
	   this.setLayout(new GridLayout(0,4));
	   for(int i=0;i<holdings.length;i++)
	   {
		   Holding currentholding=holdings[i];
		   
		   // panel to contain the labels
		   JPanel cellPanel=new JPanel();
		   //the labels should be displayed on top of each other
		   cellPanel.setLayout(new BoxLayout(cellPanel,BoxLayout.PAGE_AXIS));
		   
		   //labels
		   JLabel code=new JLabel("Holding Code: "+currentholding.getCode());
		   JLabel title=new JLabel("Title: "+currentholding.getTitle());
		   JLabel fee=new JLabel("Standard Loan Fee: $"+currentholding.getDefaultLoanFee());
		   JLabel period=new JLabel("Loan Period: "+currentholding.getMaxLoanPeriod());
		   
		   //add labels to panel
		   cellPanel.add(code);
		   cellPanel.add(title);
		   cellPanel.add(fee);
		   cellPanel.add(period);
		   
		   // add panel to scroll pane
		   JScrollPane scrollPane=new JScrollPane(cellPanel);
		 
		   //do the border
		   if(currentholding instanceof Book)
			   scrollPane.setBorder(BorderFactory.createLineBorder(Color.BLUE, 10));
		   else
			   scrollPane.setBorder(BorderFactory.createLineBorder(Color.RED,10));
   
		   
		   this.add(scrollPane);
		   
	   }
	   
	   //Add empty ones
	   int emptytoAdd;
	   if(holdings.length<=4) //no empty ones to add
		   return;
	   
	   //there are some emptys to add so add them
	   emptytoAdd=4-holdings.length%4;
	   for(int i=0;i<emptytoAdd;i++)
	   {
		   JPanel cellPanel=new JPanel();
		   cellPanel.setBackground(Color.WHITE);
		   cellPanel.setBorder(BorderFactory.createLineBorder(Color.BLACK));
		   this.add(cellPanel);
	   }
	   
   }
   
   // provide getter for the "view" instance
   public LMSMainView getMainView() {
      return view;
   }
   
   
   
  
}
