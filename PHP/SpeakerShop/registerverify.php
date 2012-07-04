<?php
$_SESSION['firstname']=$_POST['firstname'];
$_SESSION['lastname']=$_POST['lastname'];
$_SESSION['age']=$_POST['age'];
$_SESSION['address']=$_POST['address'];
$_SESSION['city']=$_POST['city'];
$_SESSION['email']=$_POST['email'];

if(isset($_POST['submit']))
{
	if(empty($_SESSION['firstname'])) 
	{ 
		echo "First name must be filled out";
		return;
	}

	if(empty($_SESSION['lastname']))
	{
		echo "Last name must be filled out";
		return;
	}	


	if($_SESSION['age']<16 | $_SESSION['age']>90)
	{
		echo "You are not of applicable age to be a member (16-90).";
		return;
	}

	if(empty($_SESSION['email']))
	{
		echo "Email must be filled out!";
		return;
	}

 	//ereg is deprecated so i used preg_match
 	 @$regex = $strict? '/^([.0-9a-z_-]+)@(([0-9a-z-]+\.)+[0-9a-z]{2,4})$/i' : '/^([*+!.&#$¦\'\\%\/0-9a-z^_`{}=?~:-]+)@(([0-9a-z-]+\.)+[0-9a-z]{2,4})$/i' 
  	; 
  	if (!preg_match($regex, trim($_SESSION['email']))) { 

  		echo "Email is not in the correct format !";
 		return;

	}
 


	$content="Firstname=".$_SESSION['firstname']."&lastname=".$_SESSION['lastname']."&age=".$_SESSION['$age']."&address=".$_SESSION['address']."&city=".$_SESSION['city']."&email=".$_SESSION['email'];

	@mail("sarina_mccormack@exemail.com.au","Member registration", $content,"webmaster@hifidelity.com");

	//attempt to open users.txt for writing in append mode
	$fp = @fopen ("users.txt", "a");
	//file didnt exist so just open straight for writing
	if($fp==FALSE)
		$fp=@fopen("users.txt","w");
		
	//NEW LINE NOT WORKING FOR SOME REASON
	fwrite($fp,$content."\n\r");
	fclose($fp);

	echo "Thank you for registering ".$_SESSION['firstname']." ".$_SESSION['lastname']."!";
	return;
}

?>