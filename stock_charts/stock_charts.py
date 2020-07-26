# python3
class StockCharts:
    def read_data(self):
        n, k = map(int, input().split())
        stock_data = [list(map(int, input().split())) for i in range(n)]
        return stock_data

    def write_response(self, result):
        print(result)

    def converter(self,stock_data,n,k):
        adj_matrix = [[0]*n for _ in range(n)]
        for i in range(n):
            for j in range(n):
                Isedge = True
                for t in range(k):
                    if(stock_data[i][t]>=stock_data[j][t]):
                        Isedge = False
                        break
                if Isedge:
                    adj_matrix[i][j] = 1
        return adj_matrix

    def dfs(self, adj_matrix,matching,seen,u,n):
        for v in range(n):
            if adj_matrix[u][v]==1 and seen[v]==False:
                seen[v] = True
                if(matching[v]<0 or self.dfs(adj_matrix,matching,seen,matching[v],n)):
                    matching[v] = u
                    return True
        return False


    def min_charts(self, stock_data):
        # Replace this incorrect greedy algorithm with an
        # algorithm that correctly finds the minimum number
        # of charts on which we can put all the stock data
        # without intersections of graphs on one chart.
        n = len(stock_data)
        k = len(stock_data[0])
        adj_matrix = self.converter(stock_data,n,k)
        matching = [-1]*n
        ans = 0
        for u in range(n):
            seen = [False]*n 
            if(self.dfs(adj_matrix,matching,seen,u,n)):
                ans += 1
        return n-ans

    def solve(self):
        stock_data = self.read_data()
        result = self.min_charts(stock_data)
        self.write_response(result)

if __name__ == '__main__':
    stock_charts = StockCharts()
    stock_charts.solve()
