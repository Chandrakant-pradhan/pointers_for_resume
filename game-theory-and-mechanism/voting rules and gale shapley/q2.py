import matplotlib.pyplot as plt
from typing import Dict, List, Tuple

def Gale_Shapley(suitor_prefs, reviewer_prefs) -> Dict[str, str]:
    '''
        Gale-Shapley Algorithm for Stable Matching

        Parameters:
        suitor_prefs: dict - Dictionary of suitor preferences
        reviewer_prefs: dict - Dictionary of reviewer preferences

        Returns:
        matching: dict - Dictionary of suitor matching with reviewer
    '''

    # Each suitor is free initially
    free_suitors = list(suitor_prefs.keys())
    # To track proposals
    proposals = {s: [] for s in suitor_prefs}
    # Current matches
    matches = {}

    # Create a ranking dictionary for reviewers for quick comparison
    reviewer_rank = {
        r: {s: i for i, s in enumerate(prefs)} for r, prefs in reviewer_prefs.items()
    }

    while free_suitors:
        suitor = free_suitors.pop(0)
        # Get his preference list
        prefs = suitor_prefs[suitor]

        # Propose to the next reviewer he hasn’t proposed yet
        for reviewer in prefs:
            if reviewer not in proposals[suitor]:
                proposals[suitor].append(reviewer)

                if reviewer not in matches:
                    # Reviewer is free → accept
                    matches[reviewer] = suitor
                else:
                    # Reviewer already matched → check preference
                    current_suitor = matches[reviewer]
                    if reviewer_rank[reviewer][suitor] < reviewer_rank[reviewer][current_suitor]:
                        # Reviewer prefers new suitor → switch
                        matches[reviewer] = suitor
                        free_suitors.append(current_suitor)  # old suitor becomes free
                    else:
                        # Reviewer rejects → suitor remains free
                        free_suitors.append(suitor)
                break

    # Convert reviewer→suitor mapping to suitor→reviewer mapping
    matching = {s: r for r, s in matches.items()}
    return matching


def avg_suitor_ranking(suitor_prefs: Dict[str, List[str]], matching: Dict[str, str]) -> float:
    '''
        Calculate the average ranking of suitor in the matching
    '''
    total_rank = 0
    n = len(suitor_prefs)
    for suitor, reviewer in matching.items():
        total_rank += suitor_prefs[suitor].index(reviewer) + 1  # +1 for 1-based rank
    return total_rank / n


def avg_reviewer_ranking(reviewer_prefs: Dict[str, List[str]], matching: Dict[str, str]) -> float:
    '''
        Calculate the average ranking of reviewer in the matching
    '''
    total_rank = 0
    n = len(reviewer_prefs)
    for suitor, reviewer in matching.items():
        total_rank += reviewer_prefs[reviewer].index(suitor) + 1
    return total_rank / n


def get_preferences(file) -> Tuple[Dict[str, List[str]], Dict[str, List[str]]]:
    '''
        Get the preferences from the file
    '''
    suitor_prefs = {}
    reviewer_prefs = {}

    for line in file:
        if line[0].islower():
            reviewer, prefs = line.strip().split(' : ')
            reviewer_prefs[reviewer] = prefs.split()
        else:
            suitor, prefs = line.strip().split(' : ')
            suitor_prefs[suitor] = prefs.split()
        
    return suitor_prefs, reviewer_prefs


if __name__ == '__main__':

    avg_suitor_ranking_list = []
    avg_reviewer_ranking_list = []

    for i in range(100):
        with open('data/data_'+str(i)+'.txt', 'r') as f:
            suitor_prefs, reviewer_prefs = get_preferences(f)

            matching = Gale_Shapley(suitor_prefs, reviewer_prefs)

            avg_suitor_ranking_list.append(avg_suitor_ranking(suitor_prefs, matching))
            avg_reviewer_ranking_list.append(avg_reviewer_ranking(reviewer_prefs, matching))

    plt.hist(avg_suitor_ranking_list, bins=10, label='Suitor', alpha=0.5, color='r')
    plt.hist(avg_reviewer_ranking_list, bins=10, label='Reviewer', alpha=0.5, color='g')

    plt.xlabel('Average Ranking')
    plt.ylabel('Frequency')
    plt.legend()
    plt.savefig('q2.png')

