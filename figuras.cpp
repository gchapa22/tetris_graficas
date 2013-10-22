//figuras.cpp
// http://en.wikipedia.org/wiki/Tetris#Colors_of_Tetriminos

void figuraI()
{
    matriz[0][10] = 1; piezas[0].renglon = 0; piezas[0].columna = 10;
    matriz[1][10] = 1; piezas[1].renglon = 1; piezas[1].columna = 10;
    matriz[2][10] = 1; piezas[2].renglon = 2; piezas[2].columna = 10;
    
    piezas[3].renglon = -1; piezas[3].columna = -1;
    
    columnaMenor = 10;
    filaInferior = 2;
}

void figuraO()
{
    matriz[0][10] = 1; piezas[0].renglon = 0; piezas[0].columna = 10;
    matriz[0][11] = 1; piezas[1].renglon = 0; piezas[1].columna = 11;
    matriz[1][10] = 1; piezas[2].renglon = 1; piezas[2].columna = 10;
    matriz[1][11] = 1; piezas[3].renglon = 1; piezas[3].columna = 11;
    
    columnaMenor = 10;
    filaInferior = 1;
}


void figuraS()
{
    matriz[0][11] = 1; piezas[0].renglon = 0; piezas[0].columna = 11;
    matriz[0][12] = 1; piezas[1].renglon = 0; piezas[1].columna = 12;
    matriz[1][10] = 1; piezas[2].renglon = 1; piezas[2].columna = 10;
    matriz[1][11] = 1; piezas[3].renglon = 1; piezas[3].columna = 11;
    
    columnaMenor = 10;
    filaInferior = 1;
}

void figuraZ()
{
    matriz[0][10] = 1; piezas[0].renglon = 0; piezas[0].columna = 10;
    matriz[0][11] = 1; piezas[1].renglon = 0; piezas[1].columna = 11;
    matriz[1][11] = 1; piezas[2].renglon = 1; piezas[2].columna = 11;
    matriz[1][12] = 1; piezas[3].renglon = 1; piezas[3].columna = 12;
    
    columnaMenor = 10;
    filaInferior = 1;
}


void figuraT()
{
    matriz[0][11] = 1; piezas[0].renglon = 0; piezas[0].columna = 11;
    matriz[1][10] = 1; piezas[1].renglon = 1; piezas[1].columna = 10;
    matriz[1][11] = 1; piezas[2].renglon = 1; piezas[2].columna = 11;
    matriz[1][12] = 1; piezas[3].renglon = 1; piezas[3].columna = 12;
    
    columnaMenor = 10;
    filaInferior = 1;
}


void figuraL()
{
    matriz[0][10] = 1; piezas[0].renglon = 0; piezas[0].columna = 10;
    matriz[1][10] = 1; piezas[1].renglon = 1; piezas[1].columna = 10;
    matriz[2][10] = 1; piezas[2].renglon = 2; piezas[2].columna = 10;
    matriz[2][11] = 1; piezas[3].renglon = 2; piezas[3].columna = 11;
    
    columnaMenor = 10;
    filaInferior = 2;
}


void figuraJ()
{
    matriz[0][10] = 1; piezas[0].renglon = 0; piezas[0].columna = 10;
    matriz[0][11] = 1; piezas[1].renglon = 0; piezas[1].columna = 11;
    matriz[1][11] = 1; piezas[2].renglon = 1; piezas[2].columna = 11;
    matriz[2][11] = 1; piezas[3].renglon = 2; piezas[3].columna = 11;
    
    columnaMenor = 10;
    filaInferior = 2;
}

