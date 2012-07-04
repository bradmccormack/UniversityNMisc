<?php session_start();?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN"
"http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">

<html xmlns="http://www.w3.org/1999/xhtml">
<head>
<title>Brads Speaker Shop </title>
<meta name="Description" content="Brads speaker shop" />
<meta name="Keywords" content="css layout" />
<meta http-equiv="Content-Type" content="text/html; charset=iso-8859-1"/>
<link rel="stylesheet" href="template.css" type="text/css" />
</head>
<body>
<div id="wrapper">
    <div id="header">
          <?php require("header.php");?>
    </div>

    <div id="nav">
    	<?php require("navbar.php");?>
    </div>
    
    <div id="main">
    
    <p>
    Hi Fidelity sound provides packages according to your listening requirements. <br/>
    Whether you listen to 2 Channel Stereo music in absolute detail
    Or if you want impacting, awe inspiring home theatre package.
    </p>



	<a  class="biglink" href="productlist_stereo.php">2 Channel / Stereo</a> <br/>
	<img  class="center" src="pictures/stereo.jpg" alt="2 Channel Speakers Clipart"/>
	
		
		
	<p>
	If you have an articulated ear and enjoy extreme realism from your music then a 2 channel setup is what you are after.<br/>
	Hi Fidelity Sound offers speakers that provide an experience so pristine you would swear you are having a real life performance right in front of you.
	</p>

	<a  class="biglink" href="productlist_surround.php">5.1 Channel / Home Theatre</a> <br/>
   
    <img  class="center" src="pictures/surround.jpg" alt="Surround Speakers Clipart" /> 
    
    <p>
    Perhaps you are not as interested in extreme realism and are after a room shattering, impacting experience.<br/>
    Hi Fidelity sound can tailor a surround package that will make you swear that the action is happening right in your listening environment.
    </p>
  
	</div>
	
      <div id="footer">
    	<?php require("footer.php"); ?>
    </div>
    
</div>
    
</body>
</html>