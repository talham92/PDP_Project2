

task void squareroot(uniform float a[],uniform int itorBegin, uniform int count)
{
	foreach (i=0...count)
	{
		float k=1.0;	// k hold value of the next approximation.
		float N=a[i];

		while(abs(k-sqrt(N))>0.0001)
		{
			k=(k+(N/k))/2;		
		}
		a[i]=k;
	}
}

export void squareroot_ispc_tasks(uniform float a[], uniform int count,uniform int numTasks)
{
	
	launch[numTasks] squareroot(a,0,count);
	sync;
}
  
