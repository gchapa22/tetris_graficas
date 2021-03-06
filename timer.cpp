float t=-1.0;
float delta=0.01;
int n;
int m;
int pos[2] = {0,2}

void llenaMatriz()
{
	for ( int i = 0; i < n; i++ )
    	for ( int j = 0; j < m; j++ )
    	{
    		a[i][j] = 0;
    	}
}

void MueveCuadro()
{
	t += delta;
	glutPostRedisplay();
    glutTimerFunc(15,myTimer,1);
    for ( int i = 0; i < n; i++ )
    	for ( int j = 0; j < m; j++ )
    	{
        	if(a[i][j]==1 && a[i-1][j] == 0)
        	{
        		a[i][j]=0;
        		a[i-1][j]=1;
        	}
        	else
        	{
        		for(int k = 0;k < m; k++)
        		{
        			int lleno = 0;
        			if(a[n][k]==1)
        			{
        				lleno = 1;
        			}
        			else
        			{
        				lleno = 0;
        			}
        		}
        		if(lleno==1)
        		{
        			for(int k = 0;k < m; k++)
        			{
        				a[n][k] = 0;
        			}
        		}
        		a[0][rand() % m]=1;
        		j = m;
        	}
    	}
}

void MueveCuadro()
{
	t += delta;
	glutPostRedisplay();
    glutTimerFunc(15,myTimer,1);

    if(a[pos[0]][pos[1]] == 1 && a[pos[0]-1][pos[1]] == 0)
    {
    	a[pos[0]][pos[1]]=0;
    	a[pos[0]-1][pos[1]]=1;
    	pos[0]-=1;
    }
    else
    {
    	for(int k = 0;k < m; k++)
        {
        	int lleno = 0;
        	if(a[n][k]==1)
        	{
        		lleno = 1;
        	}
        	else
        	{
        		lleno = 0;
        	}
        }
        if(lleno==1)
        {
        	for(int k = 0;k < m; k++)
        	{
        		a[pos[0]][k] = 0;
        	}
        }
    	pos[0] = 0;
    	pos[1] = rand() % m;
    	a[0][pos[1]]=1;
    }
}
