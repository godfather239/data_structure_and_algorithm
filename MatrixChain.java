package org.example;


/**
 * 矩阵链乘法
 * Author: godfather239
 * Date:  2023/5/18
 */
public class MatrixChain {
    // 最小代价矩阵
    private long[][] m;

    // 最优解划分位置矩阵，m[i][j]对应的括号划分位置k
    private int[][] s;

    // 输入矩阵链
    private int[] p;

    // 矩阵链长度
    private int n;

    public MatrixChain(int[] p) {
        this.p = p;
        n = p.length - 1;
        matrixChainOrder(this.p);
    }

    /**
     * 返回最优解对应的全括号形式
     * @return
     */
    public String getOptimalParens() {
        /**
         * 输出格式：
         * (p1*p2)*(p3*(p4*p5))
         */
        return getOptimalParensKernel(1, n);
    }

    /**
     * 返回最优解对应的代价
     * @return
     */
    public long getMinOrderPrice() {
        return m[1][n];
    }

    private String getOptimalParensKernel(int i, int j) {
        if (i == j) {
            return "p" + i;
        }
        int k = s[i][j];
        return "(" + getOptimalParensKernel(i, k) + getOptimalParensKernel(k + 1, j) + ")";
    }

    /**
     * 计算最优代价矩阵
     * @param p 矩阵链输入，p[i],p[i+1]表示矩阵Ai的行数和列数
     */
    private void matrixChainOrder(int[] p) {
        // m, s数组长度都为n+1，这样m[i][j]才能表达矩阵链i->j
        m = new long[n+1][n+1];
        s = new int[n+1][n+1];
        // 矩阵初始化
        for (int i = 1; i <= n; ++i) {
            m[i][i] = 0;
        }
        /**
         * 自底向上构建矩阵
         * 三层循环
         * 第一层：子矩阵链长度，从2 -> n，记l
         * 第二层：矩阵链起始位置，从1 -> n-l+1，记i
         * 第三层：划分位置遍历，从i -> j-1，记k，注：j = i + l - 1
         * 第三层逻辑：
         *  对于所有可能的划分位置一一考察，取最小值作为m[i][j]的最终值，并保存k
         */
        for (int l = 2; l <= n; ++l) {
            // 之所以从1开始，是因为p[0]p[1]一起表示第一个矩阵
            for (int i = 1; i <= n - l + 1; ++i) {
                int j = i + l - 1;
                m[i][j] = Long.MAX_VALUE;
                for (int k = i; k <= j - 1; ++k) {
                    long q = m[i][k] + m[k+1][j] + (long) p[i - 1] * p[k] * p[j];
                    if (q < m[i][j]) {
                        m[i][j] = q;
                        s[i][j] = k;
                    }
                }
            }
        }
    }
}
