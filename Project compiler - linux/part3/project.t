function int foo2(real a)
{
	var int a;
	a=23;
	if(a==23){ a=10;}
	else { a=19;}
	return a;
	

}

function void main()
{
	var int a,b;
	a=0;
	while(a<10){
	b=foo2(3.14);
	a=a+b;
}
	return;
}
