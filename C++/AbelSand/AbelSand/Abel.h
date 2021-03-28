namespace abel
{
	const int kLatticeSize = 1025;  
	const int kLatticeToBeAdded = kLatticeSize/2;

	const int kDx[4] = {1,0,-1,0};
	const int kDy[4] = {0,1,0,-1};

	struct LCoord
	{
		unsigned int x;
		unsigned int y;
	};

	double MoveStandard(unsigned int n, unsigned int ih);        // performs Abelian sandpile toppling 1 by 1 
	double MoveStandard_1Step(unsigned int n,unsigned int ih);  // performs toppling of Abelian sandpile by larger mass
	double ahaha(unsigned int n,unsigned int** previous_z_lat);
	double ahaha2(unsigned int n, unsigned int** previous_z_lat);

}