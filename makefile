all: test
PLATFORM = mac64
INC      = /Library/ntl-9.1.0/include/
CC       = gcc
CPP      = g++
CARGS    = -m64 -O2
RELEASE := $(shell uname -r | cut -f 1 -d .)
ifneq ($(RELEASE), 11)
	CPPSTDLIB = -stdlib=libc++
endif
CPPLIB   = -L/Library/ntl-9.1.0/lib/ -lntl -lm -lgmp $(CPPSTDLIB)
SRCS     = paillier.cpp NTAlgorithm.cpp SHACommit.cpp SHA256.cpp Article.cpp PublicBoard.cpp Auction.cpp Commitment.cpp PairRep.cpp ComparisonProofCommitments.cpp ComparisonProof.cpp AuctionProofCommitments.cpp AuctionProof.cpp SignedCommitment.cpp Bidpackage.cpp Auctioneer.cpp Seller.cpp Player.cpp Buyer.cpp Challenge.cpp ChallengeAddition.cpp ChallengeMultiplication.cpp RevealComparisonAddition.cpp RevealComparisonMultiplication.cpp ComReveal.cpp BidderInfo.cpp DSA.cpp
OBJS     = $(subst .cpp,.o,$(SRCS))

test: test.cpp $(OBJS)
	$(CPP) $(CARGS) test.cpp $(OBJS) -o test -I$(INC) $(CPPLIB)

paillier.o: paillier.cpp paillier.h
	$(CPP) $(CARGS) -c paillier.cpp -I$(INC)
	
NTAlgorithm.o: NTAlgorithm.cpp NTAlgorithm.h
	$(CPP) $(CARGS) -c NTAlgorithm.cpp -I$(INC)
	
SHACommit.o: SHACommit.cpp SHACommit.h SHA256.o
	$(CPP) $(CARGS) -c SHACommit.cpp -I$(INC)

SHA256.o: SHA256.h SHA256.cpp
	$(CPP) $(CARGS) -c SHA256.cpp -I$(INC)

Article.o: Article.h Article.cpp
	$(CPP) $(CARGS) -c Article.cpp

Auctioneer.o: Auctioneer.h Auctioneer.cpp Auction.o AuctionProof.o PublicBoard.o Bidpackage.o Article.o Challenge.o
	$(CPP) $(CARGS) -c Auctioneer.cpp -I$(INC)

Challenge.o: Challenge.h Challenge.cpp
	$(CPP) $(CARGS) -c Challenge.cpp

ChallengeAddition.o: ChallengeAddition.h ChallengeAddition.cpp Challenge.o
	$(CPP) $(CARGS) -c ChallengeAddition.cpp -I$(INC)

ChallengeMultiplication.o: ChallengeMultiplication.h ChallengeMultiplication.cpp Challenge.o
	$(CPP) $(CARGS) -c ChallengeMultiplication.cpp -I$(INC)

AuctionProof.o: AuctionProof.h AuctionProof.cpp ComparisonProof.o AuctionProofCommitments.o ComparisonProofCommitments.o
	$(CPP) $(CARGS) -c AuctionProof.cpp -I$(INC)

ComparisonProof.o: ComparisonProof.h ComparisonProof.cpp PairRep.o NTAlgorithm.o Commitment.o ComReveal.o
	$(CPP) $(CARGS) -c ComparisonProof.cpp -I$(INC)

AuctionProofCommitments.o: AuctionProofCommitments.h AuctionProofCommitments.cpp ComparisonProofCommitments.o
	$(CPP) $(CARGS) -c AuctionProofCommitments.cpp -I$(INC)

ComparisonProofCommitments.o: ComparisonProofCommitments.h ComparisonProofCommitments.cpp Commitment.o
	$(CPP) $(CARGS) -c ComparisonProofCommitments.cpp -I$(INC)

PublicBoard.o: PublicBoard.h PublicBoard.cpp Auction.o
	$(CPP) $(CARGS) -c PublicBoard.cpp -I$(INC)

Auction.o: Auction.h Auction.cpp Bidpackage.o Article.o
	$(CPP) $(CARGS) -c Auction.cpp -I$(INC)

Bidpackage.o: Bidpackage.h Bidpackage.cpp PairRep.o SignedCommitment.o
	$(CPP) $(CARGS) -c Bidpackage.cpp -I$(INC)

PairRep.o: PairRep.h PairRep.cpp
	$(CPP) $(CARGS) -c PairRep.cpp -I$(INC)

SignedCommitment.o: SignedCommitment.h SignedCommitment.cpp Commitment.o
	$(CPP) $(CARGS) -c SignedCommitment.cpp -I$(INC)

Commitment.o: Commitment.h Commitment.cpp SHACommit.o
	$(CPP) $(CARGS) -c Commitment.cpp -I$(INC)

Player.o: Player.h Player.cpp Article.o
	$(CPP) $(CARGS) -c Player.cpp -I$(INC)

Seller.o: Seller.h Seller.cpp Article.o
	$(CPP) $(CARGS) -c Seller.cpp -I$(INC)

Buyer.o: Buyer.h Buyer.cpp Article.o
	$(CPP) $(CARGS) -c Buyer.cpp -I$(INC)

RevealComparisonAddition.o: RevealComparisonAddition.h RevealComparisonAddition.cpp ComparisonProof.o
	$(CPP) $(CARGS) -c RevealComparisonAddition.cpp -I$(INC)

RevealComparisonMultiplication.o: RevealComparisonMultiplication.h RevealComparisonMultiplication.cpp ComparisonProof.o
	$(CPP) $(CARGS) -c RevealComparisonMultiplication.cpp -I$(INC)
	
DSA.o: DSA.h DSA.cpp SHA256.o
	$(CPP) $(CARGS) -c DSA.cpp -I$(INC)

ComReveal.o: ComReveal.h ComReveal.cpp Commitment.o
	$(CPP) $(CARGS) -c ComReveal.cpp -I$(INC)

BidderInfo.o: BidderInfo.h BidderInfo.cpp BidPackage.o ComparisonProofCommitments.o
	$(CPP) $(CARGS) -c BidderInfo.cpp -I$(INC)

clean:
	rm -rf *.o *_c *_c++ *.class *.log *.rlp *.lp *.bas *.ilp *.dSYM
