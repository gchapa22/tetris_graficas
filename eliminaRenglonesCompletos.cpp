void eliminaRenglonesCompletos(){
    bool lleno=true;
      for(int x=RENGLONES; x>=0; x--)
      {
        lleno=true;
        for(int y=0;y<COLUMNAS; y++)
        {
          if(matriz[y][x]==0)
          {
            lleno = false;
          }
        }
        if(lleno)
        {
          puntos+=100;
          for(int k=x;k<RENGLONES-1; k++)
          {
            for(int r=0;r<COLUMNAS; r++)
            {
              matriz[r][k]=matriz[r][k+1];
            }
          }
          lleno = true;
          velocidad/=1.2;
        }
      }
}
