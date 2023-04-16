#ifndef BANKING_H
#define BANKING_H

class Investment {
public:
	Investment();
	void setInitialDeposit(double initialDeposit);
	double getInitialDeposit();
	void setMonthlyDeposit(double monthlyDeposit);
	double getMonthlyDeposit();
	void setAnnualInterest(double annualInterest);
	double getAnnualInterest();
	void setYears(int years);
	int getYears();

	void startingInformation();



private:
	double m_initialDeposit;
	double m_monthlyDeposit;
	double m_annualInterest;
	int m_years;
};

#endif
