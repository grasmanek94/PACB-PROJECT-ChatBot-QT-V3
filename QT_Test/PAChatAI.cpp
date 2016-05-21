#include <vector>
#include <tuple>
#include <functional>
#include "PAChatAI.h"

//random question, random comment after answer received, random adders, is this an possible answer? if yes how to process answer, false = next chat
using qp = std::tuple< 
	QStringList, // 0 - questions
	QStringList, // 1 - reactions to answers to questions
	QStringList, // 2 - random adder to questions
	QStringList, // 3 - random adder to answers
	std::function<bool(QString)>, // 4 - check if this is an possible answer, false=ignore, true=invoke answer processing
	std::function<bool(QString,bool*,int*)>,  // 5 - process answer, false = disconnect chat, true = next question
	int, // 6 - the question ask time
	int // 7 - time for typing reaction
>;

std::vector<qp> questions_answers =
{
	qp(
		QStringList{ 
			"j/m?", "jm?", "jm?", "jm?", "Jm?", "jm?", "JM?", "jm?", "J/m?", "jm?", "J/M?", "jm?", "jongen/meisje?", "jm?", "jongen of meisje?", "jm?", "j m?", "jm?", "J m?", "jm?", "J M?", "jm?", "j M?", "jm?", "jongen/meid?", "jm?", 
			"hoi, j/m?", "jm?", "hoi, jm?", "jm?", "hoi, Jm?", "jm?", "hoi, JM?", "jm?", "hoi, J/m?", "jm?", "hoi, J/M?", "jm?", "hoi, jongen/meisje?", "jm?", "hoi, jongen of meisje?", "jm?", "hoi, j m?", "jm?", "hoi, J m?", "jm?", "hoi, J M?", "jm?", "hoi, j M?", "jm?", "hoi, jongen/meid?", "jm?",
			"hoi j/m?", "jm?", "hoi jm?", "jm?", "hoi Jm?", "jm?", "hoi JM?", "jm?", "hoi J/m?", "jm?", "hoi J/M?", "jm?", "hoi jongen/meisje?", "jm?", "hoi jongen of meisje?", "jm?", "hoi j m?", "jm?", "hoi J m?", "jm?", "hoi J M?", "jm?", "hoi j M?", "jm?", "hoi jongen/meid?", "jm?",
			"hey, j/m?", "jm?", "hey, jm?", "jm?", "hey, Jm?", "jm?", "hey, JM?", "jm?", "hey, J/m?", "jm?", "hey, J/M?", "jm?", "hey, jongen/meisje?", "jm?", "hey, jongen of meisje?", "jm?", "hey, j m?", "jm?", "hey, J m?", "jm?", "hey, J M?", "jm?", "hey, j M?", "jm?", "hey, jongen/meid?", "jm?",
			"hey j/m?", "jm?", "hey jm?", "jm?", "hey Jm?", "jm?", "hey JM?", "jm?", "hey J/m?", "jm?", "hey J/M?", "jm?", "hey jongen/meisje?", "jm?", "hey jongen of meisje?", "jm?", "hey j m?", "jm?", "hey J m?", "jm?", "hey J M?", "jm?", "hey j M?", "jm?", "hey jongen/meid?", "jm?",
			"haai, j/m?", "jm?", "haai, jm?", "jm?", "haai, Jm?", "jm?", "haai, JM?", "jm?", "haai, J/m?", "jm?", "haai, J/M?", "jm?", "haai, jongen/meisje?", "jm?", "haai, jongen of meisje?", "jm?", "haai, j m?", "jm?", "haai, J m?", "jm?", "haai, J M?", "jm?", "haai, j M?", "jm?", "haai, jongen/meid?", "jm?",
			"haai j/m?", "jm?", "haai jm?", "jm?", "haai Jm?", "jm?", "haai JM?", "jm?", "haai J/m?", "jm?", "haai J/M?", "jm?", "haai jongen/meisje?", "jm?", "haai jongen of meisje?", "jm?", "haai j m?", "jm?", "haai J m?", "jm?", "haai J M?", "jm?", "haai j M?", "jm?", "haai jongen/meid?", "jm?",
			"hooi, j/m?", "jm?", "hooi, jm?", "jm?", "hooi, Jm?", "jm?", "hooi, JM?", "jm?", "hooi, J/m?", "jm?", "hooi, J/M?", "jm?", "hooi, jongen/meisje?", "jm?", "hooi, jongen of meisje?", "jm?", "hooi, j m?", "jm?", "hooi, J m?", "jm?", "hooi, J M?", "jm?", "hooi, j M?", "jm?", "hooi, jongen/meid?", "jm?",
			"hooi j/m?", "jm?", "hooi jm?", "jm?", "hooi Jm?", "jm?", "hooi JM?", "jm?", "hooi J/m?", "jm?", "hooi J/M?", "jm?", "hooi jongen/meisje?", "jm?", "hooi jongen of meisje?", "jm?", "hooi j m?", "jm?", "hooi J m?", "jm?", "hooi J M?", "jm?", "hooi j M?", "jm?", "hooi jongen/meid?"
		},
		QStringList{ "ik J", "ik jongen", "jongen hier", "j hier", "hier j", "hiero j" },
		QStringList{ "", " :)", "", " :P", "", " ;)", "", " :D", "", " ;D", "", " ;P", "" },
		QStringList{ 
			"21", " bijna 21", " hihi 21", " hehe 21", ", al een tijdje 21",
			"21", " bijna 21", " hihi 21", " hehe 21", ", al een tijdje 21",
			"21", " bijna 21", " hihi 21", " hehe 21", ", al een tijdje 21",
			"21", " bijna 21", " hihi 21", " hehe 21", ", al een tijdje 21",
			"21", " bijna 21", " hihi 21", " hehe 21", ", al een tijdje 21",
			"21", " bijna 21", " hihi 21", " hehe 21", ", al een tijdje 21",
			"21 :)", " bijna 21 :)", " hihi 21 :)", " haha 21 :)", ", al een tijdje 21 :)",
			"21 :P", " bijna 21 :P", " hihi 21 :P", " haha 21 :P", ", al een tijdje 21 :P",
			"21 ;)", " bijna 21 ;)", " hihi 21 ;)", " haha 21 ;)", ", al een tijdje 21 ;)",
			"21 :D", " bijna 21 :D", " hihi 21 :D", " haha 21 :D", ", al een tijdje 21 :D",
			"21 ;D", " bijna 21 ;D", " hihi 21 ;D", " haha 21 ;D", ", al een tijdje 21 ;D",
			"21 ;P", " bijna 21 ;P", " hihi 21 ;P", " haha 21 ;P", ", al een tijdje 21 ;P",
			"21", " bijna 21", " hihi 21", " hehe 21", ", al een tijdje 21",
			"21", " bijna 21", " hihi 21", " hehe 21", ", al een tijdje 21",
			"21", " bijna 21", " hihi 21", " hehe 21", ", al een tijdje 21",
			"21", " bijna 21", " hihi 21", " hehe 21", ", al een tijdje 21",
			"21", " bijna 21", " hihi 21", " hehe 21", ", al een tijdje 21",
			"21", " bijna 21", " hihi 21", " hehe 21", ", al een tijdje 21"
		},
		[&](QString answer)
		{
			const static QStringList possible_answers = { "d", "m", "v", "0", "1", "2", "3", "4", "5", "6", "7", "8", "9" };
			for (auto& possible_answer : possible_answers)
			{
				if (answer.indexOf(possible_answer) != -1)
				{
					return true;
				}
			}
			return false;
		},
		[&](QString answer, bool* got_age, int* determined_age)
		{
			//filter already filters this, try determine age here
			QString s_number;
			int digits = 0;
			for (auto& c : answer)
			{
				if (c.isDigit())
				{
					s_number += c;
					++digits;
				}
			}
			bool ok;
			int age = s_number.toInt(&ok);
			if (got_age)
			{
				*got_age = digits != 0 && ok;
				if (determined_age)
				{
					*determined_age = age;
				}
			}

			return digits == 0 || (ok && age > 15 && age < 21);
		},
		2000,
		3000
	),

	qp(
		QStringList{ "en jouw leeftijd?", "en wat is je leeftijd?", "en hoe oud ben jij?", "en hoeveel jaartjes heb jij erop zitten?", "en je leeftijd?", "en jou leeftijd?" },
		QStringList{ "" },
		QStringList{ "", " :)", "", " :P", "", " ;)", "", " :D", "", " ;D", "", " ;P", "" },
		QStringList{ "", " :)", "", " :P", "", " ;)", "", " :D", "", " ;D", "", " ;P", "" },
		[&](QString answer)
		{
			for (auto& c : answer)
			{
				if (c.isDigit())
				{
					return true;
				}
			}
			return false;
		},
		[&](QString answer, bool*, int*)
		{
			QString s_number;
			for (auto& c : answer)
			{
				if (c.isDigit())
				{
					s_number += c;
				}
			}
			bool ok;
			int age = s_number.toInt(&ok);
			return ok && age > 15 && age < 21;
		},
		3000,
		2000
	),

	qp(
		QStringList{ "zoek je iemand om mee te daten?", "wil je 'n x in 't echt ontmoeten?", "wil je een keertje echt ontmoeten?", "zou je durven te ontmoeten voor een date?", "zou je mij misschien als vriendje willen?", "wil je misschien een sexdate?" },
		QStringList{ "want ik wel met jou" },
		QStringList{ "", " :)", "", " :P", "", " ;)", "", " :D", "", " ;D", "", " ;P", "" },
		QStringList{ "", " :)", "", " :P", "", " ;)", "", " :D", "", " ;D", "", " ;P", "" },
		[&](QString answer)
		{
			const static QStringList possible_answers = {"ja", "yes", "ok", "nee", "may", "mab", "nah", "niet", "mis", "jup", "mwah", "waarom", "mischien", "hoezo", "nooit", "altijd", "hangt", "kan", "zou", "kun", "helaas", "prim", "top", "goed" };
			for (auto& possible_answer : possible_answers)
			{
				if (answer.indexOf(possible_answer) != -1)
				{
					return true;
				}
			}
			return false;
		},
		[&](QString answer, bool*, int*)
		{
			const static QStringList possible_answers = { "ja", "yes", "ok", "mis", "may", "mab" };
			for (auto& possible_answer : possible_answers)
			{
				if (answer.indexOf(possible_answer) != -1)
				{
					return true;
				}
			}
			return false;
		},
		3500,
		3000
	),

	qp(
		QStringList{ "oke :D en vlakbij welke stad woon je?", "en waar woon je?", "en wat is je woonplaats?", "waar woon je?" },
		QStringList{ "ik vlakbij Eindhoven", "ik in Eindhoven", "ik bij Eindhoven", "ik vlakbij Geldrop", "ik in Geldrop", "ik bij Geldrop", "Ik vlakbij Blixembosch", "Ik in Blixembosch", "Ik bij Blixembosch", "ik vlakbij Meerhoven", "ik in Meerhoven", "ik bij Meerhoven", "ik vlakbij Veldhoven", "ik in Veldhoven", "ik bij Veldhoven", "ik vlakbij Nuenen", "ik in Nuenen", "ik bij Nuenen", "ik vlakbij Nederwetten", "ik in Nederwetten", "ik bij Nederwetten" },
		QStringList{ "", " :)", "", " :P", "", " ;)", "", " :D", "", " ;D", "", " ;P", "" },
		QStringList{ "", " :)", "", " :P", "", " ;)", "", " :D", "", " ;D", "", " ;P", "" },
		[&](QString answer)
		{
			return true;
		},	
		[&](QString answer, bool*, int*)
		{
			return true;
		},
		3500,
		4000
	),

	qp(
		QStringList{ "te ver voor je om te ontmoeten?" },
		QStringList{ "ik kan elke afstand hebben" },
		QStringList{ "", " :)", "", " :P", "", " ;)", "", " :D", "", " ;D", "", " ;P", "" },
		QStringList{ "", " :)", "", " :P", "", " ;)", "", " :D", "", " ;D", "", " ;P", "" },
		[&](QString answer)
		{
			const static QStringList possible_answers = { "ja", "yes", "ok", "nee", "nah", "niet", "mis", "may", "mab", "jup", "mwah", "waarom", "mis", "mischien", "hoezo", "nooit", "altijd", "hangt", "te ", "zou", "ver", "kan", "kun", "helaas", "prim", "top", "goed", "luk" };
			for (auto& possible_answer : possible_answers)
			{
				if (answer.indexOf(possible_answer) != -1)
				{
					return true;
				}
			}
			return false;
		},	
		[&](QString answer, bool*, int*)
		{
			const static QStringList possible_answers = { "nee", "nah", "niet", "misschien", "waarom", "mis", "may", "mab", "nooit", "niet te ver", "kan", "kunnen" };
			for (auto& possible_answer : possible_answers)
			{
				if (answer.indexOf(possible_answer) != -1)
				{
					return true;
				}
			}
			return false;
		},
		3000,
		3000
	),

	qp(
		QStringList{ "wil je verder chatten op whatsapp? ik wel want deze site werkt klote.." },
		QStringList{ "als je geinterreseerd bent: mijn whatsapp: 06-30269976, ik wacht wel op een appje van je ;) doeei" },
		QStringList{ "", " :)", "", " :P", "", " ;)", "", " :D", "", " ;D", "", " ;P", "" },
		QStringList{ "", " :)", "", " :P", "", " ;)", "", " :D", "", " ;D", "", " ;P", "" },
		[&](QString answer)
		{
			const static QStringList possible_answers = { "ja", "yes", "ok", "nee", "nah", "niet", "mis", "may", "mab", "jup", "mwah", "waarom", "mischien", "hoezo", "nooit", "altijd", "hangt", "te ", "zou", "ver", "kan", "kun", "helaas", "prim", "top", "goed", "luk" };
			for (auto& possible_answer : possible_answers)
			{
				if (answer.indexOf(possible_answer) != -1)
				{
					return true;
				}
			}
			return false;
		},	
		[&](QString answer, bool*, int*)
		{
			const static QStringList possible_answers = { "ja", "yes", "ok", "jup", "top", "goed", "prim", "mis", "may", "mab" };
			for (auto& possible_answer : possible_answers)
			{
				if (answer.indexOf(possible_answer) != -1)
				{
					return true;
				}
			}
			return false;
		},
		4000,
		3000
	)
};

PAChatAI::PAChatAI(QObject *parent)
	: QObject(parent)
{
	filter_ = new PAChatClientFilter(this);

	connect(&question_akser_, &QTimer::timeout, this, &PAChatAI::onAskNextQuestion);
	connect(&reaction_sender_, &QTimer::timeout, this, &PAChatAI::onReactionToAnswer);
	connect(&waiting_answer_timeout_, &QTimer::timeout, this, &PAChatAI::onWaitForAnswerTimeout);
}

PAChatAI::~PAChatAI()
{

}

void PAChatAI::Start()
{
	current_index_ = 0;
	amount_incomming_messages_ = 0;

	got_age_ = false;
	AskNextQuestion();
}

void PAChatAI::Stop()
{
	waiting_answer_timeout_.stop();
	question_akser_.stop();
	reaction_sender_.stop();
	state_ = PAChatAIState_Done;
}

bool PAChatAI::Stopped()
{
	return !question_akser_.isActive() && !reaction_sender_.isActive() && !waiting_answer_timeout_.isActive();
}

QString PAChatAI::GetQuestion(size_t index)
{
	QStringList& questions = std::get<0>(questions_answers[index]);
	QStringList& adders = std::get<2>(questions_answers[index]);
	return questions[qrand() % questions.size()] + adders[qrand() % adders.size()];
}

QString PAChatAI::GetReaction(size_t index)
{
	QStringList& reactions = std::get<1>(questions_answers[index]);
	QStringList& adders = std::get<3>(questions_answers[index]);
	return reactions[qrand() % reactions.size()] + adders[qrand() % adders.size()];
}

bool PAChatAI::IsPossibleAnswer(size_t index, QString message)
{
	return std::get<4>(questions_answers[index])(message);
}

bool PAChatAI::IsGoodAnswer(size_t index, QString message, bool* did_extract_age, int* extracted_age)
{
	return std::get<5>(questions_answers[index])(message, did_extract_age, extracted_age);
}

void PAChatAI::AskNextQuestion()
{
	state_ = PAChatAIState_AskingQuestion;
	reaction_sender_.stop();
	int time = std::get<6>(questions_answers[current_index_]);
	question_akser_.start(time);
}

void PAChatAI::PushNextReaction()
{
	state_ = PAChatAIState_SendingReaction;
	question_akser_.stop();
	int time = std::get<7>(questions_answers[current_index_]);
	reaction_sender_.start(time);
}


void PAChatAI::ProcessMessage(QString message)
{
	if (state_ == PAChatAIState_Done || state_ == PAChatAIState_Failed)
	{
		return;
	}

	message = message.toLower();

	if (++amount_incomming_messages_ < 4)
	{
		if (filter_->IsMessageFiltered(message))
		{
			state_ = PAChatAIState_Failed;
			emit requestNextChat();
			return;
		}
	}

	if (!got_age_)
	{
		int got_age_count = 0;
		IsGoodAnswer(0, message, &got_age_, &got_age_count);
		if (got_age_)
		{
			if (got_age_count < 16 || got_age_count > 20)
			{
				state_ = PAChatAIState_Failed;
				emit requestNextChat();
				return;
			}
		}
	}

	if (state_ != PAChatAIState_WaitingForAnswer && current_index_ != 0) // skip if first question (asking gender, mostly they do tell it themselves)
	{
		return;
	}

	if (IsPossibleAnswer(current_index_, message))
	{
		if (IsGoodAnswer(current_index_, message, &got_age_))
		{
			waiting_answer_timeout_.stop();
			PushNextReaction();
		}
		else
		{
			state_ = PAChatAIState_Failed;
			emit requestNextChat();
			return;
		}
	}
}

void PAChatAI::onAskNextQuestion()
{
	question_akser_.stop();
	emit onRequestMessage(GetQuestion(current_index_), false);
	state_ = PAChatAIState_WaitingForAnswer;
	waiting_answer_timeout_.start(60000);
}

void PAChatAI::onReactionToAnswer()
{
	reaction_sender_.stop();

	QString reaction = GetReaction(current_index_);
	bool not_last = ++current_index_ < questions_answers.size();

	emit onRequestMessage(reaction, !not_last);

	if (not_last)
	{
		if (got_age_ && current_index_ == 1)
		{
			++current_index_;
		}
		AskNextQuestion();
	}
	else
	{
		Stop();
	}
}

void PAChatAI::onWaitForAnswerTimeout()
{
	state_ = PAChatAIState_Failed;
	emit requestNextChat();
}