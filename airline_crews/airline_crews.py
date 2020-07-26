# python3
class MaxMatching:
    def read_data(self):
        n, m = map(int, input().split())
        adj_matrix = [list(map(int, input().split())) for i in range(n)]
        return adj_matrix

    def write_response(self, matching):
        line = [str(-1 if x == -1 else x + 1) for x in matching]
        print(' '.join(line))

    def dfs(self,adj_matrix,matching, seen,u,n,m):
        for v in range(m):
            if adj_matrix[u][v]==1 and seen[u][v]==False:
                seen[u][v] = True
                if(matching[v]<0 or self.dfs(adj_matrix,matching,seen,matching[v],n,m)):
                    matching[v] = u
                    return True
        return False

    def find_matching(self, adj_matrix):
        # Replace this code with an algorithm that finds the maximum
        # matching correctly in all cases.
        n = len(adj_matrix)
        m = len(adj_matrix[0])
        matching = [-1] * m
        seen = [[False]*m for _ in range(n)]
        for u in range(n):
            self.dfs(adj_matrix,matching,seen,u,n,m)

        ret = [-1]*n
        for v in range(m):
            if matching[v]!=-1:
                ret[matching[v]] = v        
        return ret

    def solve(self):
        adj_matrix = self.read_data()
        matching = self.find_matching(adj_matrix)
        self.write_response(matching)

if __name__ == '__main__':
    max_matching = MaxMatching()
    max_matching.solve()
