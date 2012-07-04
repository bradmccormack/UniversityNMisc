//make sure that the element is not empty
function validate_empty(field,msg)
{
	if(field.value.length==0 )
	{
		alert(msg);
		field.focus();
		return false;
	}
	return true;
}

//make sure a element is a number and lies within the range specified
function validate_range(field,min,max,msg)
{
	var num=parseInt(field.value);
    if (!isNaN(num) && (num>=min && num<=max)) 
			return true;
	
	alert(msg);
	field.focus();
	return false;
}

//make sure an element contains text that matches standard email syntax
function validate_email(field,msg)
{
	//use regular expressions.. suitable for this low demand website. If it was high volume i wouldnt use regex due to overhead
	var emailExp = /^[\w\-\.\+]+\@[a-zA-Z0-9\.\-]+\.[a-zA-z0-9]{2,4}$/;
	if(field.value.match(emailExp))
		return true;
	
	else
	{
		alert(msg);
		field.focus();
		return false;
	}

}

//validate the whole form
function validate_form(thisform)
{

  //Validate for mandatory fields against empty
  if (!validate_empty(document.getElementById('firstname'),"First name must be filled out!"))
  	return false;
  
  
  if(!validate_empty(document.getElementById('lastname'),"Last name must be filled out !"))
  	return false;

  if (!validate_empty(document.getElementById('email'),"Email must be filled out!"))
  	return false;
  
   //It says between 16 and 90 i assume this means inclusive
  if(!validate_range(document.getElementById('age'),16,90,"You are not of applicable age to be a member. (Between 16 and 90)"))
  	return false;
  	
  	
  //validate against faulty email input
  if(!validate_email(document.getElementById('email'),"Email not in the correct format!"))
  	return false;
 

}

