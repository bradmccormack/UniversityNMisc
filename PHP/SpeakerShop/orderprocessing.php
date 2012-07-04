<?php session_start();

if(isset($_POST['confirmed']))
{
	$_SESSION['creditcard_number']=$_POST['creditcardnumber'];
	$_SESSION['creditcard_expiry']=$_POST['creditcardexpiry'];
	header("location: confirmation.php");
}


?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN"
"http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">

<html xmlns="http://www.w3.org/1999/xhtml">
<head>
<title>Hi Fidelity Audio - Order Processing Page </title>
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

    	<h3> Your Order Details </h3>
    	<?php
    	echo "<td><form method=post>";
    	
    	echo "<h4> Payment Amount </h4>";		
    	echo "Total amount to be paid AUD$".$_SESSION['totalcost'];
    	
    	echo "<h4> Shipping Details </h4>";
    	echo "Customer: ".$_SESSION['firstname']." ".$_SESSION['lastname']."<br/>";
    	echo "Address: ".$_SESSION['address']."<br/>";
    	echo "City: ".$_SESSION['city']."<br/>";
    	echo "Email: ".$_SESSION['email']."<br/>";
    	
    	echo "<h4> Credit Card Details </h4>";
 
    	echo "<input type=radio name=card id=amex value=amex>";
		echo "<label for=amex>";
		echo "<img class=logo src=pictures/amex.jpg alt=amex picture>";
		echo "</label>";
		
    	echo "<input type=radio name=card id=mastercard value=mastercard>";
		echo "<label for=mastercard>";
		echo "<img class=logo src=pictures/mastercard.jpg alt=mastercard picture>";
		echo "</label>";
    	
    	echo "<input type=radio name=card id=visa value=visa>";
		echo "<label for=visa>";
		echo "<img class=logo src=pictures/visa.jpg alt=visa picture>";
		echo "</label><br/><br/>";
		
		echo "Card Number <input type=text name=creditcardnumber id=creditcardnumber> ";
		echo "Expiry (mm/yyyy) <input type=text name=creditcardexpiry id=creditcardexpiry >";
		
    	
		echo "<br><input type=submit name=confirmed value=Confirm>";
		echo "<input type=hidden name=h1 value=\"".$productinfo[1]."\"/>";
		echo "<input type=hidden name=h2 value=\"".$productinfo[3]."\"/>";
		echo "</form> </td>";
    	
    	?>
    	
	</div>
	
      <div id="footer">
    	<?php require("footer.php"); ?>
    </div>
    
</div>
    
</body>
</html>