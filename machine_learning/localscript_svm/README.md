static_raw_.yar
静态/解混淆代码匹配特征

emulation_.yar
JS引擎模拟行为匹配特征

feature_extractor.py
抽取特征，dump  data/target，训练模型

svm_predict.py
跑sample，生成判断的csv，如果传入参数为sample dir，先salineup扫描再预测；如果传入参数为behavior dir，将文件夹名改为XXresult，直接预测