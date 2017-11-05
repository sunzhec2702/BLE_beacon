import java.util.List;

import org.apache.commons.math3.linear.Array2DRowRealMatrix;
import org.apache.commons.math3.linear.DecompositionSolver;
import org.apache.commons.math3.linear.LUDecomposition;
import org.apache.commons.math3.linear.RealMatrix;

public class LocationCalculator {
	List<LocationElement> elements;

	
	LocationCalculator(List<LocationElement> elements) {
		this.elements = elements;
	}
	
	public RealMatrix locationCalculate() {
		int elementSize = this.elements.size();
		if (elementSize < 3) {
			return null;
		}
		Array2DRowRealMatrix A = new Array2DRowRealMatrix(elementSize - 1, 2);
		Array2DRowRealMatrix B = new Array2DRowRealMatrix(elementSize - 1, 1);
		for (int i = 1; i < elementSize; i++) {
			A.setEntry(i - 1, 0, 2 * (this.elements.get(0).station.x - this.elements.get(i).station.x));
			A.setEntry(i - 1, 1, 2 * (this.elements.get(0).station.y - this.elements.get(i).station.y));
		}

		double constData = Math.pow(this.elements.get(0).station.x, 2) + Math.pow(this.elements.get(0).station.y, 2);
		for (int i = 1; i < elementSize; i++) {
			double p1 = (Math.pow(this.elements.get(i).station.x, 2) + Math.pow(this.elements.get(i).station.y, 2));
			double p2 = Math.pow(this.elements.get(i).distanceToStation, 2) - Math.pow(this.elements.get(0).distanceToStation, 2);
			B.setEntry(i - 1, 0, constData - p1 + p2);
		}
		
		RealMatrix A_T = A.transpose();
		DecompositionSolver solver = new LUDecomposition(A_T.multiply(A)).getSolver();
		RealMatrix result_tmp  = solver.getInverse();
		RealMatrix result = (result_tmp.multiply(A_T).multiply(B)); 
		if (result.getColumnDimension() != 1 || result.getRowDimension() != 2) {
			return null;
		}
		return result;
	}
}
