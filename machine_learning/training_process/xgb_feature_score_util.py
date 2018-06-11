import pickle
import operator


def load_obj_from_pickle(filename):
    with open(filename, 'rb') as fh:
        return pickle.load(fh)

def print_feature_scores(feature_score):
    print('Length of feature score: %d' % len(feature_score))
    sorted_scores = sorted(feature_score.items(), key=operator.itemgetter(1), reverse=True)
    # print(sorted_scores)
    for item in sorted_scores:
        value = item[1]*'*'
        print('%6s|%s' % (item[0], value))

if __name__ == '__main__':
    feature_score = load_obj_from_pickle('xgb_feature_score.pkl')
    print_feature_scores(feature_score)