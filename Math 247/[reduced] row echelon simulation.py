from fractions import Fraction
import numpy as np

def printMatrix( mat):
    for row in mat :
        for col in row:
            print(col , end=' ')
        print()
    print()

def rowEchelon(npmatrix , n, m):
    """
        1. pivots are scaled to 1
    """
    rownum = 0
    for colnum in range(int(n)):
        first_nonzero_rownum = rownum 
        while first_nonzero_rownum != m and npmatrix[first_nonzero_rownum][colnum] == 0 :
            first_nonzero_rownum = first_nonzero_rownum +1
        if first_nonzero_rownum != m:
            if rownum != first_nonzero_rownum:
                print('R',rownum+1 , ' <-> ' ,'R' , first_nonzero_rownum+1,sep='')
                npmatrix[[rownum , first_nonzero_rownum ]] = npmatrix[[first_nonzero_rownum , rownum]]
                printMatrix(npmatrix)
            
            if npmatrix[rownum][colnum]  != 1 :
                vag = npmatrix[rownum][colnum]
                print('R',rownum+1 , ' -> ' , 'R' , rownum +1,'/' , vag  , sep='')
                npmatrix[rownum] = npmatrix[rownum] / vag
                printMatrix(npmatrix)

            assert npmatrix[rownum][colnum] == 1


            for nicher_rownum in range(rownum + 1,int(m)):

                if npmatrix[nicher_rownum][colnum] != 0:
                    
                    gun = - npmatrix[nicher_rownum][colnum] / npmatrix[rownum][colnum]
                    
                    print('R',nicher_rownum+1, ' -> ' , 'R' , nicher_rownum + 1 , ' + ' , gun ,'*' , 'R' , rownum + 1  ,sep='')
                    npmatrix[nicher_rownum] = npmatrix[nicher_rownum] + npmatrix[rownum]  * gun 
                    printMatrix(npmatrix)

                assert npmatrix[nicher_rownum][colnum] == 0

            rownum = rownum + 1

def reducedRowEchelon(npmatrix, n ,m):

    pivots = list()

    rownum = 0
    for colnum in range(int(n)):
        first_nonzero_rownum = rownum 
        while first_nonzero_rownum != m and npmatrix[first_nonzero_rownum][colnum] == 0 :
            first_nonzero_rownum = first_nonzero_rownum +1
        if first_nonzero_rownum != m:
            if rownum != first_nonzero_rownum:
                print('R',rownum+1 , ' <-> ' ,'R' , first_nonzero_rownum+1,sep='')
                npmatrix[[rownum , first_nonzero_rownum ]] = npmatrix[[first_nonzero_rownum , rownum]]
                printMatrix(npmatrix)
            
            pivots.append((rownum , colnum))

            if npmatrix[rownum][colnum]  != 1 :
                vag = npmatrix[rownum][colnum]
                print('R',rownum+1 , ' -> ' , 'R' , rownum +1,'/' , vag  , sep='')
                npmatrix[rownum] = npmatrix[rownum] / vag
                printMatrix(npmatrix)

            assert npmatrix[rownum][colnum] == 1


            for nicher_rownum in range(rownum + 1,int(m)):

                if npmatrix[nicher_rownum][colnum] != 0:
                    gun = - npmatrix[nicher_rownum][colnum] / npmatrix[rownum][colnum]

                    print('R',nicher_rownum+1, ' -> ' , 'R' , nicher_rownum + 1 , ' + ' , gun ,'*' , 'R' , rownum + 1  ,sep='')
                    npmatrix[nicher_rownum] = npmatrix[nicher_rownum] + npmatrix[rownum]  * gun 
                    printMatrix(npmatrix)
                
                assert npmatrix[nicher_rownum][colnum] == 0
            rownum = rownum + 1

    pivots.reverse()
    for (rownum , colnum) in pivots:
        for uporer_rownum in range(rownum-1 , -1 , -1 ):
            
            if npmatrix[uporer_rownum][colnum]  != 0:
                gun = - npmatrix[uporer_rownum][colnum]/npmatrix[rownum][colnum]

                print('R',uporer_rownum+1, ' -> ' , 'R' , uporer_rownum + 1 , ' + ' , gun ,'*' , 'R' , rownum + 1  ,sep='')
                npmatrix[uporer_rownum] = npmatrix[uporer_rownum] + npmatrix[rownum]  * gun 
                printMatrix(npmatrix)
            
            assert npmatrix[uporer_rownum][colnum] == 0


def main():
    n,m=map( Fraction  , input('[number of variable]  [number of equations] ').strip().split() )
    print('n  =  ' , n , 'm = ',m)
    inp = list()
    for _ in range(int(m)) :
        inp.append(list(map(Fraction , input().strip().split() )))
    #printMatrix(inp)
    
    npmatrix = np.array(inp).astype('object')
    printMatrix(npmatrix)
    
    rowEchelon(npmatrix , n ,m) 
    print('row echelon completed: ')
    printMatrix(npmatrix)

    
    reducedRowEchelon(npmatrix , n ,m) 
    print('reduced row echelon completed: ')
    printMatrix(npmatrix)






if __name__ == '__main__':
    main()