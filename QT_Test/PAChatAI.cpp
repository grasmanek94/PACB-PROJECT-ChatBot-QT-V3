#include <vector>
#include <tuple>
#include <functional>
#include "PAChatAI.h"

//random question, random comment after answer received, random adders, is this an possible answer? if yes how to process answer, false = next chat
using qp = std::tuple< 
	QStringList, // 0 - questions
	QStringList, // 1 - reactions to answers to questions
	QStringList, // 2 - random adder to both questions and reactions
	std::function<bool(QString)>, // 3 - check if this is an possible answer, false=ignore, true=invoke answer processing
	std::function<bool(QString)>  // 4 - process answer, false = disconnect chat, true = next question
>;

std::vector<qp> questions_answers =
{
	qp(
		QStringList{ 
			"j/m?", "jm?", "Jm?", "JM?", "J/m?", "J/M?", "jongen/meisje?", "jongen of meisje?", "j m?", "J m?", "J M?", "j M?", "jongen/meid?", 
			"hoi, j/m?", "hoi, jm?", "hoi, Jm?", "hoi, JM?", "hoi, J/m?", "hoi, J/M?", "hoi, jongen/meisje?", "hoi, jongen of meisje?", "hoi, j m?", "hoi, J m?", "hoi, J M?", "hoi, j M?", "hoi, jongen/meid?",
			"hoi j/m?", "hoi jm?", "hoi Jm?", "hoi JM?", "hoi J/m?", "hoi J/M?", "hoi jongen/meisje?", "hoi jongen of meisje?", "hoi j m?", "hoi J m?", "hoi J M?", "hoi j M?", "hoi jongen/meid?",
			"hey, j/m?", "hey, jm?", "hey, Jm?", "hey, JM?", "hey, J/m?", "hey, J/M?", "hey, jongen/meisje?", "hey, jongen of meisje?", "hey, j m?", "hey, J m?", "hey, J M?", "hey, j M?", "hey, jongen/meid?",
			"hey j/m?", "hey jm?", "hey Jm?", "hey JM?", "hey J/m?", "hey J/M?", "hey jongen/meisje?", "hey jongen of meisje?", "hey j m?", "hey J m?", "hey J M?", "hey j M?", "hey jongen/meid?",
			"haai, j/m?", "haai, jm?", "haai, Jm?", "haai, JM?", "haai, J/m?", "haai, J/M?", "haai, jongen/meisje?", "haai, jongen of meisje?", "haai, j m?", "haai, J m?", "haai, J M?", "haai, j M?", "haai, jongen/meid?",
			"haai j/m?", "haai jm?", "haai Jm?", "haai JM?", "haai J/m?", "haai J/M?", "haai jongen/meisje?", "haai jongen of meisje?", "haai j m?", "haai J m?", "haai J M?", "haai j M?", "haai jongen/meid?",
			"hooi, j/m?", "hooi, jm?", "hooi, Jm?", "hooi, JM?", "hooi, J/m?", "hooi, J/M?", "hooi, jongen/meisje?", "hooi, jongen of meisje?", "hooi, j m?", "hooi, J m?", "hooi, J M?", "hooi, j M?", "hooi, jongen/meid?",
			"hooi j/m?", "hooi jm?", "hooi Jm?", "hooi JM?", "hooi J/m?", "hooi J/M?", "hooi jongen/meisje?", "hooi jongen of meisje?", "hooi j m?", "hooi J m?", "hooi J M?", "hooi j M?", "hooi jongen/meid?"
		},
		QStringList{ "ik J", "ik jongen", "jongen hier", "j hier" },
		QStringList{ " :)", " :P", " ;)", " :D", " ;D", " ;P" },
		[&](QString answer)
		{
			return true;
		},
		[&](QString answer)
		{
			//filter already filters this
			return true;
		}
	),

	qp(
		QStringList{ "leeftijd?", "wat is je leeftijd?", "hoe oud ben je?", "hoeveel jaartjes?", "en je leeftijd?" },
		QStringList{ "ik 21", "ik bijna 21", "hihi 21", "haha 21", "ik 22", "ik bijna 22", "hihi 22", "haha 22", "ik 20", "al een tijdje 20", "hihi 20", "haha 20" },
		QStringList{ " :)", " :P", " ;)", " :D", " ;D", " ;P" },
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
		[&](QString answer)
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
			return ok && age > 16 && age < 21;
		}
	),

	qp(
		QStringList{ "zoek je iemand om mee te daten?", "wil je 'n x in 't echt ontmoeten?", "wil je een keertje echt ontmoeten?", "zou je durven te ontmoeten voor een date?", "zou je mij misschien als vriendje willen?", "wil je misschien een sexdate?" },
		QStringList{ "want ik wel met jou" },
		QStringList{ " :)", " :P", " ;)", " :D", " ;D", " ;P" },
		[&](QString answer)
		{
			const static QStringList possible_answers = {"ja", "yes", "ok", "nee", "nah", "niet", "misschien", "jup", "mwah", "waarom", "mischien", "hoezo", "nooit", "altijd", "hangt", "kan", "zou", "kun", "helaas", "prim", "top", "goed" };
			for (auto& possible_answer : possible_answers)
			{
				if (answer.indexOf(possible_answer) != -1)
				{
					return true;
				}
			}
			return false;
		},
		[&](QString answer)
		{
			const static QStringList possible_answers = { "ja", "yes", "ok", "misschien", "mischien" };
			for (auto& possible_answer : possible_answers)
			{
				if (answer.indexOf(possible_answer) != -1)
				{
					return true;
				}
			}
			return false;
		}
	),

	qp(
		QStringList{ "oke :D en vlakbij welke stad woon je?", "en waar woon je?", "en wat is je woonplaats?", "waar woon je?" },
		QStringList{ "ik vlakbij Eindhoven", "ik in Eindhoven", "ik bij Eindhoven", "ik vlakbij Geldrop", "ik in Geldrop", "ik bij Geldrop", "Ik vlakbij Blixembosch", "Ik in Blixembosch", "Ik bij Blixembosch", "ik vlakbij Meerhoven", "ik in Meerhoven", "ik bij Meerhoven", "ik vlakbij Veldhoven", "ik in Veldhoven", "ik bij Veldhoven", "ik vlakbij Nuenen", "ik in Nuenen", "ik bij Nuenen", "ik vlakbij Nederwetten", "ik in Nederwetten", "ik bij Nederwetten" },
		QStringList{ " :)", " :P", " ;)", " :D", " ;D", " ;P" },
		[&](QString answer)
		{
			return true;
		},	
		[&](QString answer)
		{
			return true;
		}
	),

	qp(
		QStringList{ "te ver voor je om te ontmoeten?" },
		QStringList{ "ik kan elke afstand hebben" },
		QStringList{ " :)", " :P", " ;)", " :D", " ;D", " ;P" },
		[&](QString answer)
		{
			const static QStringList possible_answers = { "ja", "yes", "ok", "nee", "nah", "niet", "misschien", "jup", "mwah", "waarom", "mischien", "hoezo", "nooit", "altijd", "hangt", "te ", "zou", "ver", "kan", "kun", "helaas", "prim", "top", "goed", "luk" };
			for (auto& possible_answer : possible_answers)
			{
				if (answer.indexOf(possible_answer) != -1)
				{
					return true;
				}
			}
			return false;
		},	
		[&](QString answer)
		{
			const static QStringList possible_answers = { "nee", "nah", "niet", "misschien", "waarom", "mischien", "nooit", "niet te ver", "kan", "kunnen" };
			for (auto& possible_answer : possible_answers)
			{
				if (answer.indexOf(possible_answer) != -1)
				{
					return true;
				}
			}
			return false;
		}
	),

	qp(
		QStringList{ "wil je verder chatten op whatsapp? ik wel want deze site werkt klote.." },
		QStringList{ "als je geinterreseerd bent: mijn whatsapp: 06-30269976, ik wacht wel op een appje van je ;) doeei" },
		QStringList{ " :)", " :P", " ;)", " :D", " ;D", " ;P" },
		[&](QString answer)
		{
			const static QStringList possible_answers = { "ja", "yes", "ok", "nee", "nah", "niet", "misschien", "jup", "mwah", "waarom", "mischien", "hoezo", "nooit", "altijd", "hangt", "te ", "zou", "ver", "kan", "kun", "helaas", "prim", "top", "goed", "luk" };
			for (auto& possible_answer : possible_answers)
			{
				if (answer.indexOf(possible_answer) != -1)
				{
					return true;
				}
			}
			return false;
		},	
		[&](QString answer)
		{
			const static QStringList possible_answers = { "ja", "yes", "ok", "jup", "top", "goed", "prim" };
			for (auto& possible_answer : possible_answers)
			{
				if (answer.indexOf(possible_answer) != -1)
				{
					return true;
				}
			}
			return false;
		}
	)
};

PAChatAI::PAChatAI(QObject *parent)
	: QObject(parent)
{
	filter_ = new PAChatClientFilter(this);
	connect(&message_sender_, &QTimer::timeout, this, &PAChatAI::processNextMessage);
}

PAChatAI::~PAChatAI()
{

}

void PAChatAI::Start()
{
	current_index_ = 0;
	amount_incomming_messages_ = 0;
	message_sender_.start(500);
}

void PAChatAI::Stop()
{
	message_sender_.stop();
}

bool PAChatAI::Stopped()
{
	return !message_sender_.isActive();
}

void PAChatAI::ProcessMessage(QString message)
{
	if (++amount_incomming_messages_ < 3)
	{
		if (filter_->IsMessageFiltered(message))
		{
			Stop();
			emit requestNextChat();
			return;
		}
	}


}

void PAChatAI::processNextMessage()
{
	//emit onAnswerMessage(story_messages[l_index], !(current_index_ < story_messages.size()));
}
