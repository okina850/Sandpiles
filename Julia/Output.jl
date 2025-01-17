module Output

# supports output functionality for the results of the sandpile symulations
# outputs the final grid in CSV format, as well as an image file

using CSV
using DataFrames
using Images


function TrimZeros(A)
  # given an array A trims any zero rows/columns from its borders
  # returns a 4 tuple of integers, i1, i2, j1, j2, where the trimmed array corresponds to A[i1:i2, j1:j2]
  # A can be either numeric or a boolean array

    i1, j1 = 1, 1;
    i2, j2 = size(A);

    zz = typeof(A[1,1])(0);   # comparison of a value takes into account the type as well

    # i1 is the first row which has non zero element
    for i = 1:size(A,1)
      q = false;
      for k = 1:size(A,2)
        if A[i,k] != zz
          q = true;
          #print("found non-zero at i1, k  = ", i1, " ", k , " value = ", A[i1, k], " \n");
          i1 = i;
          break
        end
      end

      if q == true
        break
      end
    end

    # i2 is the first from below row with non zero element
    for i in size(A,1):-1:1
      q = false;
      for k = 1:size(A,2)
        if A[i,k] != zz
          q = true;
          i2 = i;
          break
        end
      end

      if q == true
        break
      end
    end

    # j1 is the first column with non zero element

    for j = 1:size(A,2)
      q = false;
      for k = 1:size(A,1)
        if A[k,j] != zz
          j1 = j;
          q = true;
          break
        end
      end

      if q == true
        break
      end
    end

    # j2 is the last column with non zero element

    for j in size(A,2):-1:1
      q=false;
      for k=1:size(A,1)
        if A[k,j] != zz
          j2 = j;
          q=true;
          break
        end
      end

      if q==true
        break
      end
    end

    return i1, i2, j1, j2;

end

function addLayerofZeros(A, extraLayer)
  # adds layer of zeros from all corners to the given array A

  if extraLayer <= 0
    return A;
  end

  N, M = size(A);


  Z = zeros( typeof(A[1,1]), N + 2*extraLayer, M + 2*extraLayer );
  Z[(extraLayer+1):(N + extraLayer ), (extraLayer+1):(M + extraLayer ) ] = A;

  return Z;

end




function printIntoFile(A, extraLayer, strFileName, TrimSmallValues = false)
  # exports a 2d matrix A into a csv file
  # @extraLayer is an integers adding layer of 0-s sorrounding the output matrix

  # trimming off very small values; tiny values affect the performance of CSV export
  if TrimSmallValues == true
    A = map( x -> if ( abs( x - floor(x)  ) < 0.01   )  floor(x) else x end, A ) ;
  end

  i1, i2, j1, j2  = TrimZeros( A );
  A = A[i1:i2, j1:j2];

  A = addLayerofZeros(A, extraLayer);

  CSV.write(string(strFileName,".csv"), DataFrame(A), writeheader = false);

  return A;

end


function Array_magnifier(A, cell_mag, border_mag)
  # A is the main array; @cell_mag is the magnifying size of the cell,
  # @border_mag is the magnifying size of the border between lattice cells

  # creates a new array where each cell of the original array A appears magnified by size = cell_mag


  total_factor = cell_mag + border_mag;

  A1 = zeros( typeof(A[1,1]), total_factor*size(A,1), total_factor*size(A,2) );

  for i = 1:size(A,1)
       for j = 1:size(A,2)
            for u = ((i-1)*total_factor +1):(i*total_factor)
            for v = ((j-1)*total_factor + 1):(j*total_factor)
               if ( ( u - (i-1)*total_factor <= cell_mag  ) && ( v - (j-1)*total_factor <= cell_mag ) )
                  A1[u, v] = A[i,j] ;
               end
            end
            end
      end
  end

  return A1;

end

function saveAsGrayImage(A, fileName, cell_mag, border_mag, TrimSmallValues = false)
    # given a 2d matrix A, we save it as a gray image after magnifying by the given factors
    A1 = Array_magnifier(A, cell_mag, border_mag);
    A1 = A1/maximum(maximum(A1));

    # trimming very small values from A1 to improve performance
    if TrimSmallValues == true
        A1 = map( x -> if ( x < 0.01 ) 0.0 else round(x, digits = 2) end, A1  ) ;
    end

    save( string(fileName, ".png") , colorview(Gray, A1)) ;
end

function saveAsRGBImage(A, fileName, color_codes, cell_mag, border_mag)
  # color_codes is a dictionary, where key is a value in A and value is an RGB triplet
  # given a 2d array A, and color codes (mapping from values in A to RGB triples), save A
  # into fileName as png image after applying the magnifying factors

  #R = zeros(size(A));
  #G = zeros(size(A));
  #B = zeros(size(A));
  A1 = Array_magnifier(A, cell_mag, border_mag);
  color_mat = zeros(UInt8, (3, size(A1,1), size(A1,2)) );

  for i = 1:size(A1,1)
    for j = 1:size(A1,2)
        color_mat[:, i,j]  = get(color_codes, A1[i,j] , [0,0,0] )
    end
  end

  #A1 = Array_magnifier(A, cell_mag, border_mag)
  save( string(fileName, ".png") , colorview(RGB, color_mat/255)) ;

end


end # end of the module
