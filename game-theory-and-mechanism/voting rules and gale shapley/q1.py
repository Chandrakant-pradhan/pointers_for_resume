import numpy as np
import itertools
from tqdm import tqdm
import matplotlib.pyplot as plt


''' Do not change anything in this function '''
def generate_random_profiles(num_voters, num_candidates):
    '''
        Generates a NumPy array where row i denotes the strict preference order of voter i
        The first value in row i denotes the candidate with the highest preference
        Result is a NumPy array of size (num_voters x num_candidates)
    '''
    return np.array([np.random.permutation(np.arange(1, num_candidates+1)) 
            for _ in range(num_voters)])


def find_winner(profiles, voting_rule):
    '''
        profiles is a NumPy array with each row denoting the strict preference order of a voter
        voting_rule is one of [plurality, borda, stv, copeland]
        In STV, if there is a tie amongst the candidates with minimum plurality score in a round, then eliminate the candidate with the lower index
        For Copeland rule, ties among pairwise competitions lead to half a point for both candidates in their Copeland score

        Return: Index of winning candidate (1-indexed) found using the given voting rule
        If there is a tie amongst the winners, then return the winner with a lower index
    '''

    winner_index = None
    
    # TODO

    if voting_rule == 'plurality':
        first_col = []
        m = len(profiles[0])
        for i in range(len(profiles)):
            first_col.append(profiles[i][0])
        #this is o(n)
        dici = {}
        for i in range(1,m+1):
            dici[i] = 0
        
        for i in range(len(first_col)):
            dici[first_col[i]]+=1

        maxi = -1
        for i,j in dici.items():
            if(j > maxi):
                maxi = j
                winner_index = i
        
    elif voting_rule == 'borda':
        dici = {}
        m = len(profiles[0])
        for i in range(1,m+1):
            dici[i] = 0
        for i in range(len(profiles)):
            for j in range(len(profiles[i])):
                dici[profiles[i][j]] += (m-j)
        
        maxi = -1
        for i,j in dici.items():
            if(j > maxi):
                maxi = j
                winner_index = i
        

    elif voting_rule == 'stv':
        is_present = {}
        m = len(profiles[0])
        for i in range(1,m+1):
            is_present[i] = True

        for i in range(m-1):
            #in each iteration find the first element frequency
            cnt = {}
            for i in range(1,m+1):
               cnt[i] = 0
            for temp in range(len(profiles)):
                for tempi in range(len(profiles[temp])):
                    if(is_present[profiles[temp][tempi]]):
                        cnt[profiles[temp][tempi]]+=1
                        break
            
            mini = np.inf
            loser = None
            for key, val in sorted(cnt.items(), key=lambda x: x[1]):
                if(val < mini and val != 0):
                    mini = val
                    loser = key
            
            is_present[loser]=False
        
        for key,val in is_present.items():
            if(val):
                winner_index = key

    elif voting_rule == 'copeland':
        cop_score = {}
        m = len(profiles[0])
        for i in range(1,m+1):
            cop_score[i]=0
        
        for i in range(1 , m+1):
            for j in range(1 , m+1):
                x = 0
                y = 0
                for k in range(len(profiles)):
                    for temp in range(len(profiles[k])):
                        if(profiles[k][temp] == i):
                            x = x+1
                            break
                        if(profiles[k][temp]==j):
                            y = y+1
                            break
                if(x>y):
                    cop_score[i] += 1
                elif(x<y):
                    cop_score[j] += 1
                else:
                    cop_score[i] += 0.5
                    cop_score[j] += 0.5
        maxi = -1
        for i,j in cop_score.items():
            if(j > maxi):
                maxi = j
                winner_index = i
        
    return winner_index


def find_winner_average_rank(profiles, winner):
    '''
        profiles is a NumPy array with each row denoting the strict preference order of a voter
        winner is the index of the winning candidate for some voting rule (1-indexed)

        Return: The average rank of the winning candidate (rank wrt a voter can be from 1 to num_candidates)
    '''

    average_rank = None

    # TODO

    for i in range(len(profiles)):
        for j in range(len(profiles[i])):
            if(profiles[i][j] == winner):
                average_rank += (j+1)
    
    average_rank = average_rank/len(profiles)

    # END TODO

    return average_rank


def check_manipulable(profiles, voting_rule, find_winner):
    '''
        profiles is a NumPy array with each row denoting the strict preference order of a voter
        voting_rule is one of [plurality, borda, stv, copeland]
        find_winner is a function that takes profiles and voting_rule as input, and gives the winner index as the output
        It is guaranteed that there will be at most 8 candidates if checking manipulability of a voting rule

        Return: Boolean representing whether the voting rule is manipulable for the given preference profiles
    '''

    manipulable = False

    # TODO
    '''
    winner = find_winner(profiles, voting_rule)
    for i in range(len(profiles)):
        prof_copy = profiles.view()
        allpermut = list(itertools.permutations(prof_copy[i]))
        for j in allpermut:
            prof_copy[i] = j
            new_winner = find_winner(prof_copy, voting_rule)
            if winner != new_winner:
                manipulable = True
                break
        if manipulable:
            break
     '''

    # END TODO

    return manipulable


if __name__ == '__main__':
    np.random.seed(420)

    num_tests = 200
    voting_rules = ['plurality', 'borda', 'stv', 'copeland']

    average_ranks = [[] for _ in range(len(voting_rules))]
    manipulable = [[] for _ in range(len(voting_rules))]
    for _ in tqdm(range(num_tests)):
        # Check average ranks of winner
        num_voters = np.random.choice(np.arange(80, 150))
        num_candidates = np.random.choice(np.arange(10, 80))
        profiles = generate_random_profiles(num_voters, num_candidates)

        for idx, rule in enumerate(voting_rules):
            winner = find_winner(profiles, rule)
            avg_rank = find_winner_average_rank(profiles, winner)
            average_ranks[idx].append(avg_rank / num_candidates)

        # Check if profile is manipulable or not
        num_voters = np.random.choice(np.arange(10, 20))
        num_candidates = np.random.choice(np.arange(4, 8))
        profiles = generate_random_profiles(num_voters, num_candidates)
        
        for idx, rule in enumerate(voting_rules):
            manipulable[idx].append(check_manipulable(profiles, rule, find_winner))


    # Plot average ranks as a histogram
    for idx, rule in enumerate(voting_rules):
        plt.hist(average_ranks[idx], alpha=0.8, label=rule)

    plt.legend()
    plt.xlabel('Fractional average rank of winner')
    plt.ylabel('Frequency')
    plt.savefig('average_ranks.jpg')
    
    # Plot bar chart for fraction of manipulable profiles
    manipulable = np.sum(np.array(manipulable), axis=1)
    manipulable = np.divide(manipulable, num_tests)
    plt.clf()
    plt.bar(voting_rules, manipulable)
    plt.ylabel('Manipulability fraction')
    plt.savefig('manipulable.jpg')
