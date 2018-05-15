--模仿c++的enum 实现
function CreateEnumTable(tbl, index)   
    local enumtbl = {}   
    local enumindex = index or 0   
    for i, v in ipairs(tbl) do   
        enumtbl[v] = enumindex + i   
    end   
    return enumtbl   
end  
--enum列表
local Attitude = CreateEnumTable({"against","guard","neutral","ally"},-1)
local Expression = CreateEnumTable({"normal","angry","happy"},-1)
local ChoiceColor = CreateEnumTable({ "white", "green", "red" },-1)

--离开函数
leave = function()end
--默认成功条件
defaultCondition = function ()
return true
end

---------------牧师 索尼的AI  ID:169----------------------------------------

ask169Why = function ()
dialog = Dialog.new()
dialog:pushSentence(Sentence.new(169, Expression.normal, "是的，先生。我们应该在任何时期都坚持做祷告。\n就算你不是本教教徒亦或者没有所属宗教，\n只要有自己所信仰的信条都可以来这里做祷告"))
dialog:pushSentence(Sentence.new(169, Expression.normal, "我们人类没有信仰的话，\n就跟那群行尸走肉没什么两样"))
dialog:pushSentence(Sentence.new(33, Expression.normal, "..."))
DialogBoxManager.getInstance():setDialog(dialog)
end

ask169Situation = function ()
dialog = Dialog.new()
dialog:pushSentence(Sentence.new(169, Expression.normal, "这里本来是个好地方，邻居们都很热情，互相帮助。\n我还记得我腰不好的时候，\n戴夫和他妻子女儿常常会过来帮忙处理教堂前的野草。"))
dialog:pushSentence(Sentence.new(169, Expression.normal, "直到它们出现了....\n大家几乎都走了..戴夫他也失去了妻子..\n虽然我想帮戴夫，他却坚持不要老人家的食物"))
dialog:pushSentence(Sentence.new(169, Expression.normal, "我只能偷偷给他女儿塞了一些罐头"))
dialog:pushSentence(Sentence.new(33, Expression.normal, "那奥诺夫呢？"))
dialog:pushSentence(Sentence.new(169, Expression.normal, "啊，他是位能干也热心的小伙子，\n经常一个人在做木工，偶尔给我们一些木制小玩意儿"))
dialog:pushSentence(Sentence.new(169, Expression.normal, "在它们出现时，他带头建起了这一带的简易围墙，\n这足以挡住它们的绝大部分，给我们带来暂时的安宁"))
dialog:pushSentence(Sentence.new(169, Expression.normal, "如果你要离开小镇，就从小镇南边一直沿着马路走就是了"))
dialog:pushSentence(Sentence.new(33, Expression.normal, "谢谢你的介绍"))
DialogBoxManager.getInstance():setDialog(dialog)
end

function create169AI()
	root = RootNode.create()--创建AI根节点
	s1 = Seletor.create()--创建AI选择节点
	root:addChild(s1)
	
	
	escape = EscapeFrom.create()--逃跑行为
	escape:setTarget(Nearest.create(Attitude.against))--保持距离行为的目标为 态度为对立的目标
	s1:addChild(escape)
	speak = Speak.create("别杀我啊！")
	escape:addChild(speak)
	
	talk = Talk.create(true)--被对话行为
	talk:setTarget(Target.create(33))--对话目标 ID：33 -Player
	dialog = Dialog.new()--对话内容
	dialog:pushSentence(Sentence.new(169, Expression.normal, "你好，我是这座教堂的牧师，我叫索尼。\n你是小镇外面来的幸存者吧，\n这里欢迎任何人来教堂做祷告。"))
	dialog:pushOption(Option.new("你在这个时候...做祷告？","ask169Why",ChoiceColor.white,"defaultCondition"))
	dialog:pushOption(Option.new("我想了解一下小镇的情况","ask169Situation",ChoiceColor.white,"defaultCondition"))
	dialog:pushOption(Option.new("离开","leave",ChoiceColor.white,"defaultCondition"))
	talk:setDialog(dialog)
	s1:addChild(talk)

	return root
end

aimanager = AIManager.getInstance()
aimanager:bindAIonNPC(create169AI(),169)


-----------  奥诺夫的AI     ID:171--------------
ask170Why = function ()
dialog = Dialog.new()
dialog:pushSentence(Sentence.new(33, Expression.normal, "真不是个好地方？"))
dialog:pushSentence(Sentence.new(171, Expression.normal, "这里也有许多幸存者来经过，\n但是都好像无法穿过小镇南边的丧尸潮，\n都死在小镇外面了"))
dialog:pushSentence(Sentence.new(171, Expression.normal, "也有幸存者死在小镇旁边不远处，\n虽然我觉得有些奇怪"))
dialog:pushSentence(Sentence.new(33, Expression.normal, "这样啊...."))
DialogBoxManager.getInstance():setDialog(dialog)
end

ask170Situation = function ()
dialog = Dialog.new()
dialog:pushSentence(Sentence.new(171, Expression.normal, "现在只能说，\n暂时勉强大概估计应该也许能撑一阵子。\n食物现在是最紧缺的物资啊"))
dialog:pushSentence(Sentence.new(171, Expression.normal, "呃，也没什么想说了"))
DialogBoxManager.getInstance():setDialog(dialog)
end

function create171AI()
	root = RootNode.create()--创建AI根节点

	parrell = Parallel.create()--创建AI并列节点
	root:addChild(parrell)
	attack = Attack.create()--攻击行为
	speak = Speak.create("去死吧        ")
	attack:addChild(speak)
	parrell:addChild(attack)
	
	s1 = Seletor.create()--创建AI选择节点
	parrell:addChild(s1)
	keepFrom = KeepFrom.create()--保持距离行为
	keepFrom:setTarget(Nearest.create(Attitude.against))--保持距离行为的目标为 态度为对立的目标
	s1:addChild(keepFrom)
	hover = Hover.create()--徘徊行为
	s1:addChild(hover)
	
	talk = Talk.create(true)--对话行为

	talk:setTarget(Target.create(33))--对话目标 ID：33   在tile文件里id：33的是Player
	dialog = Dialog.new()
	dialog:pushSentence(Sentence.new(171, Expression.normal, "你好啊，陌生人。\n你来的也许真不是个好地方。"))
	dialog:pushOption(Option.new("真不是个好地方？","ask170Why",ChoiceColor.white,"defaultCondition"))
	dialog:pushOption(Option.new("我想了解一下小镇的情况","ask170Situation",ChoiceColor.white,"defaultCondition"))
	dialog:pushOption(Option.new("离开","leave",ChoiceColor.white,"defaultCondition"))
	talk:setDialog(dialog)--对话内容
	parrell:addChild(talk)

	return root
end


aimanager:bindAIonNPC(create171AI(),171)

----------- 女孩克莱尔的AI   ID：170--------------------------


function create170AI()
	root = RootNode.create()--创建AI根节点
	s1 = Seletor.create()--创建AI选择节点
	root:addChild(s1)
	
	escape = EscapeFrom.create()--逃跑行为
	escape:setTarget(Nearest.create(Attitude.against))--保持距离行为的目标为 态度为对立的目标
	s1:addChild(escape)
	speak = Speak.create("啊呜呜呜呜！爸爸在哪！")
	escape:addChild(speak)
	
	p0 = Parallel.create()--创建AI并列节点0
	s1:addChild(p0)
	
	p1 = Parallel.create()--创建AI并列节点1
	s1:addChild(p1)
	
	talk = Talk.create(true)--被对话行为
	talk:setTarget(Target.create(33))--对话目标 ID：33 -Player
	dialog = Dialog.new()--对话内容
	dialog:pushSentence(Sentence.new(170, Expression.normal, "爸爸跟我说过不要跟陌生人说话"))
	talk:setDialog(dialog)
	p1:addChild(talk)
	
	keepFrom = KeepFrom.create()--保持距离行为
	keepFrom:setKeepDistance(50)  --保持50距离
	keepFrom:setTarget(Target.create(30))  --目标：父亲戴夫 ID30
	p1:addChild(keepFrom)
	

	
	return root
end

ai170 = create170AI();

aimanager:addDaugtherAIwhenAcceptMission1(ai170)
aimanager:bindAIonNPC(ai170,170)

-------------------- 


--[[
-NOTE
-TODO
待添加AI脚本语句和注释
--]]	

aimanager:bindAIonNPC(aimanager:createHumanAI(),30)
--aimanager:bindAIonNPC(aimanager:createGetOutAI(),358)
--aimanager:bindAIonNPC(aimanager:createGetOutAI(),359)
	
	

	
	
	
	
	
	
	