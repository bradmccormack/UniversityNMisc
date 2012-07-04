package lms.view;
import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Container;
import java.awt.FlowLayout;
import java.awt.event.KeyEvent;

import javax.swing.*;
import javax.swing.border.BevelBorder;


import lms.controller.GridDisplayPanelListener;
import lms.controller.MainViewListener;
import lms.model.facade.LMSModel;

public class LMSMainView extends JFrame {
   
   private GridDisplayPanel gridDisplay;  // "sub-view" (JPanel)
   private Container contentPane;
   private MainViewListener listener; // you should have one dedicated listener per sub-view!!!
   

   //Menu at the top
   private JMenuBar menubar; //menu for actions
   private JMenu collectionmenu;
   private JMenuItem newItem,resetItem,addItem,deleteItem;
  
   //Top Panel
   private JPanel toolbar;
   private JButton newButton,resetButton,addButton,deleteButton;
  
   
   //Status Panel at the bottom
   private JPanel statusbar;
   private JLabel codeLabel,videocountLabel,bookcountLabel;
   
   
   //... declare all other sub-views 
   //TOODO
   

   private LMSModel model;
       
   // the model should be initialised in the driver class and then passed to the main view
   public LMSMainView(LMSModel  model) {
       super("LMS System OUA 2010 Term 2");
       this.model = model;
            

       listener = new MainViewListener(this); //hookup the listener
       gridDisplay = new GridDisplayPanel (this);  // the main view is now "mapped" to a sub-view
        
       // do the same for all the other sub-views
       
     
       // GUI stuff: get content pane, set frame layout, etc.
       contentPane=this.getContentPane();
       
       
       //Setup the menu at the top
       menubar=new JMenuBar();
       newItem=new JMenuItem("New",KeyEvent.VK_N);
       newItem.addActionListener(listener);
       
       resetItem=new JMenuItem("Reset",KeyEvent.VK_R);
       resetItem.addActionListener(listener);
       
       addItem=new JMenuItem("Add",KeyEvent.VK_A);
       addItem.addActionListener(listener);
       
       deleteItem=new JMenuItem("Delete",KeyEvent.VK_D);
       deleteItem.addActionListener(listener);
       
       
       collectionmenu=new JMenu("Collection");
       collectionmenu.add(newItem);
       collectionmenu.add(resetItem);
       collectionmenu.add(addItem);
       collectionmenu.add(deleteItem);
       
       menubar.add(collectionmenu);
       this.setJMenuBar(menubar);
       
       
       //Initialize the toolbar at the top
       toolbar=new JPanel();
       newButton=new JButton("New");
       newButton.addActionListener(listener);
       
       resetButton=new JButton("Reset");
       resetButton.addActionListener(listener);
       
       addButton=new JButton("Add");
       addButton.addActionListener(listener);
       
       deleteButton=new JButton("Delete");
       deleteButton.addActionListener(listener);
       
       
       toolbar.add(newButton);
       toolbar.add(resetButton);
       toolbar.add(addButton);
       toolbar.add(deleteButton);
       toolbar.setLayout(new FlowLayout(FlowLayout.LEFT));
       toolbar.setBorder(BorderFactory.createBevelBorder(BevelBorder.RAISED));
       
       
       //Initialize the status at the bottom
       statusbar=new JPanel();
       codeLabel=new JLabel("Uninitialized");
       videocountLabel=new JLabel("0");
       bookcountLabel=new JLabel("0");
       statusbar.add(new JLabel("Collection Code -"));
       statusbar.add(codeLabel);
       statusbar.add(new JLabel("Video count -"));
       statusbar.add(videocountLabel);
       statusbar.add(new JLabel("Book count - "));
       statusbar.add(bookcountLabel);
       
       
       statusbar.setLayout(new FlowLayout(FlowLayout.LEFT));
       statusbar.setBorder(BorderFactory.createBevelBorder(BevelBorder.LOWERED));
       statusbar.setBackground(Color.WHITE);
       
       //Border layout is the parent "Layout"
       contentPane.setLayout(new BorderLayout());
       
       //Add the Toolbar at the top, the grid in the middle and the status at the bottom
       contentPane.add(toolbar,BorderLayout.NORTH);
       
       //Add the grid inside of a scrollbar so you can scroll if there is more than can fit
       
       //JScrollPane gridscroller=new JScrollPane(gridDisplay);
       //contentPane.add(gridscroller);
       
       contentPane.add(gridDisplay,BorderLayout.CENTER);
       
       
       
       contentPane.add(statusbar,BorderLayout.SOUTH);

       
   }
   
   // provide getters for all the sub-views and the model 
   public LMSModel getModel()
   {
      return this.model;
   }
   
   
   public String getCodeLabel()
   {
      return codeLabel.getText();
   }
   
   public String getVideoCount()
   {
      return videocountLabel.getText();
   }
   
   public String getBookCount()
   {
      return bookcountLabel.getText();
   }
   
   public GridDisplayPanel getGrid()
   {
	   return this.gridDisplay;
   }
   
   
   
   //setters for the model
   public void setCodeLabel(String text)
   {
      codeLabel.setText(text);
   }
   
   public void setVideoCount(String text)
   {
      videocountLabel.setText(text);
   }
   
   public void setBookCount(String text)
   {
      bookcountLabel.setText(text);
   }
   
   
   
   
}
