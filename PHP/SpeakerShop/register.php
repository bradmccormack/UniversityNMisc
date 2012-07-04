<?php session_start();?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN"
"http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">

<html xmlns="http://www.w3.org/1999/xhtml">

<head>
	<title>Brads Speaker Shop - Register</title>
	<meta name="Description" content="Brads speaker shop" />
	<meta name="Keywords" content="css layout" />
	<meta http-equiv="Content-Type" content="text/html; charset=iso-8859-1"/>
	<link rel="stylesheet" href="template.css" type="text/css" />
	<script type="text/javascript" src="validate.js"> </script>
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
    	Thank you for your interest in Hi Fidelity Sound. 
    	</p>
    
   	 	<p>
    	Becoming a member allows you access to many special offers. Please check your emails for a weekly email.
    	Some of our discounts are so amazing no competitor can match. A random winner each week will receive
    	a discount of 99%
    	</p>
    
    	<p>
    	Please fill out the form below to register as a member.
    	</p>
    
    	<div>
 		
 			<form method=post > 
				<div>
					<input type="text" name="firstname" id="firstname" 
					value="<?php if(!empty($_POST['firstname']))
						echo $_POST['firstname']; ?>"/> First name <br/>
					
					<input type="text" name="lastname" id="lastname" 
					value="<?php if(!empty($_POST['lastname']))
						echo $_POST['lastname'] ?>"/> Last name <br/>
	 				
					<input type="text" name="age" id="age" 
					value="<?php if(!empty($_POST['age']))
						echo $_POST['age'] ?>" /> Age <br/>
	 				
					<input type="text" name="address" id="address" 
					value="<?php if(!empty($_POST['address']))
						echo $_POST['address'] ?>" /> Address <br/>
					
					<input type="text" name="city" id="city" 
					value="<?php if(!empty($_POST['city']))
						echo $_POST['city'] ?>" /> City  <br/>
					
					<input type="text" name="email" id="email" 
					value="<?php if(!empty($_POST['email']))
						echo $_POST['email'] ?>" /> Email <br/>
					
					<input type="submit" value="Submit" name="submit" />
				</div>
			</form>
			<?php require("registerverify.php");?>
		</div>
	 	<br /> <br /> <br /> <br /> <br /> <br /> <br /> <br /> <br /> <br /> <br /> <br /> <br />

	</div>
	
     <div id="footer">
    	<?php require("footer.php"); ?>
    </div>
    
</div>
    
</body>
</html>