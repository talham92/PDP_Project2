
export void squareroot_ispc(uniform float a[], uniform int count)
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

