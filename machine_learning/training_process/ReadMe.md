Model Training and Scoring
===============

Platform and Pre-installation
------
1. Ubuntu 16.04 and python 2.7.*
2. Python Machine Learning Toolkit(sckit, xgboost, keras)


Usage
------
```python
python automation.py
```

Before executing automation script, please set training_set, testing_set_normal, testing_set_malicious and mid_folder in config.json

Such as following example:

```json
  "filesystem": {
    "training_set": "/home/michael/githubee/md_auto_tools/src/machine_learning/test_samples/feature/training_set.txt",
    "testing_set_normal": "/home/michael/githubee/md_auto_tools/src/machine_learning/test_samples/feature/normal_remove_empty_random_0.4_group_a.txt",
    "testing_set_malicious": "/home/michael/githubee/md_auto_tools/src/machine_learning/test_samples/feature/mal_remove_empty_random_0.3_group_b.txt",
    "mid_folder": "/home/michael/githubee/md_auto_tools/src/machine_learning/test_samples/auto_middle"
  }
```

Currently, this automatic script supports following machine learning algorithms, you could find them in "option for model"

Give a example here, if you want to train svm and xgboost, set "svm|xgboost" as value of train.model

```json
  "train": {
    "__train_comments__": {
        "option for model":"[svm|xgboost]"
    },
    "model": "svm|xgboost"
  }
```
More detailed model config could be set in "model" section

```json
  "model": {
    "svm": {
      "model_name": "svm_linear.model",
      "kernel": "linear"
    },
    "xgboost": {
      "model_name": "xgb.model",
      "nthread": 4
    }
  }
}
```


